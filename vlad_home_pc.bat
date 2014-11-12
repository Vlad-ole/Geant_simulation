REM  Setup for defining the necessary environmental variables 
REM  for Geant4 development on a Windows machine with VC++.NET

set G4INSTALL=C:\Program Files (x86)\Geant4 10.0

set G4_INCLUDE=%G4INSTALL%\include\Geant4
set G4_LIB=%G4INSTALL%\lib
set PATH=%PATH%;%G4INSTALL%\bin


REM
REM Path to my root...

set MY_G4PROJECTS=%~dp0

set > sets.txt

start B1.sln

