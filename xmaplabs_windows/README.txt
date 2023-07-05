Once the XMapsLab file has been unzipped it is ready to be used.

You will be able to see that inside the folder that has been created there is the folder "xmapslab_project" and this file that you are reading.

Inside the "xmapslab_project" folder are the three ".BAT" type files that will allow the execution of the three programs: Tools, Positions and XMapsLab.

These files are responsible for linking the "pdb" and "projects" folders inside the "binaries" folder, which is where all the programs are actually located.

In the event that this link does not occur, you will see that when you try to load a project with XMapsLab (or Positions or Tools) a blank window appears. This is probably because your filesystem is old and doesn't support links.

The easiest solution is to move the "pdb" and "projects" folders into the "binaries" folder.

The ".BAT" type files and the folder structure has been created so that the user only sees what is important and focuses only on executing the programs. But it must be taken into account that in reality all the programs and libraries that are necessary for the programs to work are found in the "binaries" folder. For this reason, by entering this folder it is also possible to execute the three programs. The condition for the three programs to work correctly is that the "pdb" and "projects" folders are in the same folder as the programs. This is achieved by links or by moving or copying as previously explained
