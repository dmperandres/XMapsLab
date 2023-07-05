cd binaries
IF NOT EXIST "projects" (
  mklink /j projects ..\projects  
)
start Positions.exe