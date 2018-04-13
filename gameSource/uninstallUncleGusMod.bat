@echo off
if EXIST objects_base\ (
  echo "Backing up mod objects folder and replacing with objects folder"
  rename objects objects_UncleGusMod
  rename objects_base objects
)
 if EXIST transitions_base\ (
  echo "Backing up mod transitions folder and replacing with transitions folder"
  rename transitions transitions_UncleGusMod
  rename transitions_base transitions
)
if EXIST categories_base\ (
  echo "Backing up mod categories folder and replacing with categories folder"
  rename categories categories_UncleGusMod
  rename categories_base categories
)
if EXIST sprites_base\ (
  echo "Backing up mod sprites folder and replacing with sprites folder"
  rename sprites sprites_UncleGusMod
  rename sprites_base sprites
)
if EXIST ground_base\ (
  echo "Backing up mod ground folder and replacing with ground folder"
  rename ground ground_UncleGusMod
  rename ground_base ground
)
if EXIST animations_base\ (
  echo "Backing up mod animations folder and replacing with animations folder"
  rename animations animations_UncleGusMod
  rename animations_base animations
)
if EXIST dataVersionNumber_base.txt (
  echo "Backing up mod dataVersionNumber file and replacing with dataVersionNumber file"
  rename dataVersionNumber.txt dataVersionNumber_UncleGusMod.txt
  rename dataVersionNumber_base.txt dataVersionNumber.txt
)
if EXIST settings\useCustomServer_base.ini (
  echo "Backing up mod useCustomServer setting and replacing with useCustomServer setting"
  rename settings\useCustomServer.ini useCustomServer_UncleGusMod.ini
  rename settings\useCustomServer_base.ini useCustomServer.ini
)
if EXIST settings\customServerAddress_base.ini (
  echo "Backing up mod customServerAddress setting and replacing with customServerAddress setting"
  rename settings\customServerAddress.ini customServerAddress_UncleGusMod.ini
  rename settings\customServerAddress_base.ini customServerAddress.ini
)
if EXIST settings\customServerPort_base.ini (
  echo "Backing up mod customServerPort setting and replacing with customServerPort setting"
  rename settings\customServerPort.ini customServerPort_UncleGusMod.ini
  rename settings\customServerPort_base.ini customServerPort.ini
)