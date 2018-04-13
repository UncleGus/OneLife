@echo off
if EXIST objects_UncleGusMod\ (
  echo "Backing up objects folder and replacing with mod objects folder"
  rename objects objects_base
  rename objects_UncleGusMod objects
)
 if EXIST transitions_UncleGusMod\ (
  echo "Backing up transitions folder and replacing with mod transitions folder"
  rename transitions transitions_base
  rename transitions_UncleGusMod transitions
)
if EXIST categories_UncleGusMod\ (
  echo "Backing up categories folder and replacing with mod categories folder"
  rename categories categories_base
  rename categories_UncleGusMod categories
)
if EXIST sprites_UncleGusMod\ (
  echo "Backing up sprites folder and replacing with mod sprites folder"
  rename sprites sprites_base
  rename sprites_UncleGusMod sprites
)
if EXIST ground_UncleGusMod\ (
  echo "Backing up ground folder and replacing with mod ground folder"
  rename ground ground_base
  rename ground_UncleGusMod ground
)
if EXIST animations_UncleGusMod\ (
  echo "Backing up animations folder and replacing with mod animations folder"
  rename animations animations_base
  rename animations_UncleGusMod animations
)
if EXIST dataVersionNumber_UncleGusMod.txt (
  echo "Backing up dataVersionNumber file and replacing with mod dataVersionNumber file"
  rename dataVersionNumber.txt dataVersionNumber_base.txt
  rename dataVersionNumber_UncleGusMod.txt dataVersionNumber.txt
)
if EXIST settings\useCustomServer_UncleGusMod.ini (
  echo "Backing up useCustomServer setting and replacing with mod useCustomServer setting"
  rename settings\useCustomServer.ini useCustomServer_base.ini
  rename settings\useCustomServer_UncleGusMod.ini useCustomServer.ini
)
if EXIST settings\customServerAddress_UncleGusMod.ini (
  echo "Backing up customServerAddress setting and replacing with mod customServerAddress setting"
  rename settings\customServerAddress.ini customServerAddress_base.ini
  rename settings\customServerAddress_UncleGusMod.ini customServerAddress.ini
)
if EXIST settings\customServerPort_UncleGusMod.ini (
  echo "Backing up customServerPort setting and replacing with mod customServerPort setting"
  rename settings\customServerPort.ini customServerPort_base.ini
  rename settings\customServerPort_UncleGusMod.ini customServerPort.ini
)