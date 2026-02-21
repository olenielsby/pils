[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{9412D128-53D3-4D56-8F8F-E8EA00C6A1CA}
AppName=PILS.maxipils
AppVerName=MAXI Diabetessimulator
AppPublisher=Teknologisk Institut og Maxi-projektet
AppPublisherURL=http://www.maxi-projektet.dk/
AppSupportURL=http://www.maxi-projektet.dk/
AppUpdatesURL=http://www.maxi-projektet.dk/
DefaultDirName={pf}\PILS.maxipils
DefaultGroupName=Maxi Diabeteshjælper
AllowNoIcons=yes
OutputDir=..\..\bin\win32
OutputBaseFilename=maxi_diabetessimulator
Compression=lzma
SolidCompression=yes
ShowLanguageDialog=yes
TimestampsInUTC=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"

[Files]
Source: "..\..\..\..\..\bin\win32\pils.exe"; DestDir: "{app}\bin\win32\"; DestName: "maxipils.exe"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\system.pils"; DestDir: "{app}\pils\english\system\"; DestName: "system.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\editor.pils"; DestDir: "{app}\pils\english\system\"; DestName: "editor.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\config.pils"; DestDir: "{app}\pils\english\system\"; DestName: "config.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\english.pils"; DestDir: "{app}\pils\english\system\"; DestName: "english.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\new.pils"; DestDir: "{app}\pils\english\system\"; DestName: "new.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\registry.pils"; DestDir: "{app}\pils\english\system\"; DestName: "registry.maxipils"; Flags: ignoreversion

Source: "..\..\..\..\..\pils\english\system\juce\juce.pils"; DestDir: "{app}\pils\english\system\juce"; DestName: "juce.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\system\juce\desktop\win32.pils"; DestDir: "{app}\pils\english\system\juce\desktop"; DestName: "win32.maxipils"; Flags: ignoreversion

Source: "..\..\..\..\..\pils\english\compute\compute.pils"; DestDir: "{app}\pils\english\compute\"; DestName: "compute.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\english\parse\xml.pils"; DestDir: "{app}\pils\english\parse\"; DestName: "xml.maxipils"; Flags: ignoreversion

Source: "..\..\..\..\..\pils\danish\system\config.pils"; DestDir: "{app}\pils\danish\system\"; DestName: "config.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\danish\system\danish.pils"; DestDir: "{app}\pils\danish\system\"; DestName: "danish.maxipils"; Flags: ignoreversion
Source: "..\..\..\..\..\pils\danish\system\new.pils"; DestDir: "{app}\pils\danish\system\"; DestName: "new.maxipils"; Flags: ignoreversion

Source: "..\..\data\*"; DestDir: "{app}\extra\danish\diabetessimulator\data\"; Excludes: "Bert Braunschweiger.pils"; Flags: ignoreversion recursesubdirs
Source: "..\..\pils\diabetessimulator.pils"; DestDir: "{app}\extra\danish\diabetessimulator\pils\"; DestName: "diabetessimulator.maxipils"; Flags: ignoreversion
Source: "..\..\pils\glukosemodel.pils"; DestDir: "{app}\extra\danish\diabetessimulator\pils\"; DestName: "glukosemodel.maxipils"; Flags: ignoreversion

Source: "..\..\data\bruger\Bert Braunschweiger.pils"; DestDir: "{userdesktop}"; DestName: "Bert Braunschweiger.maxipils"; Flags: ignoreversion

[UninstallDelete]
Type: files; Name: "{app}\pils\english\system\test.maxipils"
Type: filesandordirs; Name: "{app}\pils\registry"

[Icons]
Name: "{group}\{cm:UninstallProgram,MaxiPils}"; Filename: "{uninstallexe}"

[Registry]
Root: HKCR; Subkey: ".maxipils"; ValueType: string; ValueData: "PILS.maxipils"; Flags: uninsdeletekey
Root: HKCR; Subkey: ".maxipils\ShellNew"; ValueType: string; ValueName: "NullFile"; ValueData: " "; Flags: uninsdeletekey
Root: HKCR; Subkey: "PILS.maxipils"; ValueType: string; ValueData: "MaxiPils file"; Flags: uninsdeletekey
Root: HKCR; Subkey: "PILS.maxipils\DefaultIcon"; ValueType: string; ValueData: """{app}\extra\danish\diabetessimulator\data\grafik\diverse\maxilogo_32x32.ico"""
Root: HKCR; Subkey: "PILS.maxipils\Shell\edit\command"; ValueType: string; ValueData: """{app}\bin\win32\maxipils.exe"" -edit ""%1"""
Root: HKCR; Subkey: "PILS.maxipils\Shell\open\command"; ValueType: string; ValueData: """{app}\bin\win32\maxipils.exe"" ""%1"""
Root: HKCR; Subkey: "PILS.maxipils\Shell\register\command"; ValueType: string; ValueData: """{app}\bin\win32\maxipils.exe"" -register ""%1"""

[Run]
Filename: "{app}\bin\win32\maxipils.exe"; Parameters: "-register ""{app}\extra\danish\diabetessimulator\pils\diabetessimulator.maxipils"""

