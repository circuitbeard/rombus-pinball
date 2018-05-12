@echo off

set hexfile=C:\Users\LattePanda\Desktop\RombusPinball\Arduino\Bin\RombusPinball.hex
set avrdudeConfigfile=./avrdude.conf

echo Upgrade procedure starting.

set comportA=NONE
set comportB=NONE

if not exist %hexfile% goto error

for /f "usebackq" %%B in (`wmic path Win32_SerialPort Where "Caption LIKE '%%Leonardo%%'" Get DeviceID ^| FIND "COM"`) do set comportA=%%B

if %comportA%==NONE goto nodevice

echo Com Port for Arduino device is detected as %comportA%.
echo Reset Arduino into bootloader
mode %comportA%: baud=12 > nul

timeout 2 > nul

for /f "usebackq" %%B in (`wmic path Win32_SerialPort Where "Caption LIKE '%%Leonardo%%'" Get DeviceID ^| FIND "COM"`) do set comportB=%%B

if %comportB%==NONE goto nobldevice

echo Com Port for Arduino bootloader device is detected as %comportB%.
echo.
echo Starting AVR Downloader/Uploader.....
avrdude -C%avrdudeConfigfile% -pm32u4 -cavr109 -D -P%comportB% -b57600 -Uflash:w:%hexfile%:i

goto upgradedone

:nodevice
echo No matching module found, you should connect the module you want to upgrade.
goto end

:nobldevice
echo Reset into bootloader failed, please try again...
goto end

:error
Echo Missing parameter or file, you should provide the full filename of an existing .hex file you want to use.
goto end

:upgradedone
echo.
echo Upgrade done!

:end