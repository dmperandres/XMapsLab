cd binaries
IF NOT EXIST "projects" (
  mklink /j projects ..\projects  
)
ELSE (
  rmdir projects
  mklink /j projects ..\projects  
)
IF NOT EXIST "pdb" (
  mklink /j pdb ..\pdb
)
ELSE (
  rmdir pdb
  mklink /j pdb ..\pdb
)

start Positions.exe