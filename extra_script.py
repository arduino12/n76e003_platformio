#
# python3 script for uploading firmware to Nuvoton MCUs via NuLink programmer using their windows apps.
# arad.rgb@gmail.com 01/05/2021
#
import os.path
import warnings

Import('env')

NULINK_CLI_EXE = '"%PROGRAMFILES(X86)%\\Nuvoton Tools\\NuLink Command Tool\\NuLink.exe"'
NUMICRO_GUI_EXE = '%PROGRAMFILES(X86)%\\Nuvoton Tools\\ICPTool\\NuMicro ICP Programming Tool.exe'
NULINK_NOT_FOUND_MSG = '''
Please install %s from:
    https://www.nuvoton.com/tool-and-software/software-development-tool/programmer
'''

# select whether to upload using NULINK_CLI_EXE (USE_FASTER_NUMICRO = False) or
# using NUMICRO_GUI_EXE (USE_FASTER_NUMICRO = True) - this uses pywinauto but still much faster to upload relative to the CLI...
# USE_FASTER_NUMICRO = False
USE_FASTER_NUMICRO = True


def on_upload(source, target, env):
    firmware_path = os.path.abspath(str(source[0]))
    if USE_FASTER_NUMICRO:
        # install pywinauto if needed
        try:
            import pywinauto
        except ImportError:
            env.Execute(env.VerboseAction('$PYTHONEXE -m pip install pywinauto', 'Installing Python dependencies...'))
            warnings.warn('Please run again!')
            exit(1)

        # connect to NuMicro app (run it if needed)
        numicro_gui_exe = os.path.expandvars(NUMICRO_GUI_EXE)
        app = pywinauto.Application(backend='win32')
        # dont print 32/64bit application warning
        warnings.simplefilter('ignore')
        try:
            app.connect(path=numicro_gui_exe)
            print('Connected to NuMicro app')
        except:
            try:
                app.start(numicro_gui_exe)
                print('Started NuMicro app')
            except:
                app = None
        warnings.simplefilter('default')
        if app is None:
            warnings.warn(NULINK_NOT_FOUND_MSG % 'NuMicroICP')
            exit(2)

        # config startup dialog if needed
        window = app.window(title_re='^Nuvoton')
        window.set_focus()
        window.wait('enabled')
        if window.control_count() < 50:
            window.SelectTargetChipComboBox.select('8051 1T Series')
            window.ContinueButton.click()

        # helper to manage connection state
        def set_connection(is_connected):
            STATES = ('Disconnect', 'Connect')
            is_connected = 1 if is_connected else 0
            window.ConnectButton.wait('enabled')
            if window.ConnectButton.window_text() == STATES[is_connected]:
                window.ConnectButton.check_by_click()
                pywinauto.timings.wait_until(3, 0.1, window.ConnectButton.window_text, STATES[1 - is_connected])
                print(f'{"Connected to" if is_connected else "Disconnected from"} NuLink programmer')

        set_connection(True)
        window.set_focus()

        # flash only APROM
        window.ConfigCheckBox.uncheck_by_click()
        window.LDROMCheckBox.uncheck_by_click()
        window.APROMCheckBox.check_by_click()

        # set APROM file path if needed
        if firmware_path != window.FileNameEdit0.window_text():
            print(f'Setting APROM file to {firmware_path}')
            window.APROMButton.set_focus()
            window.APROMButton.click_input()
            app.Open.wait('enabled')
            app.Open.FileNameEdit.set_text(firmware_path)
            app.Open.OpenButton.click_input()
            window.wait('enabled')

        # handle dialogs
        window.StartButton.click_input()
        dialog = app.window(title_re='^NuMicro')
        while True:
            dialog.wait('enabled')
            text = dialog.static.window_text()
            dialog.send_keystrokes('{ENTER}{ESC}')
            if text == 'Programming flash, OK!':
                break

        set_connection(False)
        window.minimize()

    else:
        # erase APROM and write firmware to APROM 
        try:
            env.Execute(f'{NULINK_CLI_EXE} -e aprom')
            env.Execute(f'{NULINK_CLI_EXE} -w aprom {firmware_path}')
            # env.Execute(f'{NULINK_CLI_EXE} -disconnect') # doesn't disconnect....
        except:
            warnings.warn(NULINK_NOT_FOUND_MSG % 'NuLinkCLI')
            exit(2)
        # warn user to manually disconnect by pressing the button on the NuLink because -disconnect doesn't work..
        __import__('time').sleep(0.1)
        warnings.warn('''
            Press NuLink button to release (disconnect) mcu if needed!''')


env.Replace(UPLOADCMD=on_upload)
