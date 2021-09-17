import re
import time
import subprocess
import win32clipboard
import pyautogui


def copy2clip(txt):
    cmd = 'echo ' + txt.strip() + '|clip'
    return subprocess.check_call(cmd, shell=True)


def kakao2clip():
    win32clipboard.OpenClipboard()
    data = win32clipboard.GetClipboardData()
    win32clipboard.CloseClipboard()
    ret = data.split('\r')[-2]
    ret = re.search(r'\[[\S\s]+]\s\[[\S\s]+]\s(.*)', ret, re.MULTILINE).group(1)
    return ret


def main():
    print("Set Chat Box Position in 2 second")
    print('2...')
    time.sleep(1)
    print('1...')
    pos = pyautogui.position()
    print(f"Position at {pos}")
    while True:
        time.sleep(0.1)
        color = pyautogui.pixel(pos[0], pos[1])
        if color == (255, 255, 255):
            past_pos = pyautogui.position()
            pyautogui.click(pos[0], pos[1])
            pyautogui.hotkey('ctrl', 'a')
            pyautogui.hotkey('ctrl', 'c')
            string = kakao2clip()
            copy2clip(string)
            pyautogui.click(pos[0], pos[1] + 70)
            pyautogui.hotkey('ctrl', 'v')
            pyautogui.hotkey('enter')
            pyautogui.moveTo(*past_pos)
            pyautogui.click(*past_pos)
            pyautogui.click(pos[0], pos[1] + 70)


if __name__ == '__main__':
    main()
4