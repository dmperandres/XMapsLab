cd binaries
IF NOT EXIST "projects" (
  mklink /j projects ..\projects  
)
IF NOT EXIST "pdb" (
  mklink /j pdb ..\pdb
)
start XMapsLab.exe