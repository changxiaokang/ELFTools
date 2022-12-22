del /a /f /s /q ".\*.ncb"
del /a /f /s /q ".\*.sdf"
rmdir /s /q ".\ipch"

del /a /f /s /q ".\Debug\*.pdb"
del /a /f /s /q ".\Debug\*.ilk"
del /a /f /s /q ".\Debug\*.exp"

del /a /f /s /q ".\Release\*.pdb"
del /a /f /s /q ".\Release\*.ilk"
del /a /f /s /q ".\Release\*.exp"
del /a /f /s /q ".\Release\*.iobj"
del /a /f /s /q ".\Release\*.ipdb"

rmdir /s /q ".\MFCDialogPrinter\Debug"
rmdir /s /q ".\MFCDialogPrinter\Release"
rmdir /s /q ".\MFCDialogPrinter\x64"
rmdir /s /q ".\.vs"