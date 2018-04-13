if [ -d "objects_UncleGusMod" ]; then
  mv objects objects_base
  mv objects_UncleGusMod objects
fi
if [ -d "transitions_UncleGusMod" ]; then
  mv transitions transitions_base
  mv transitions_UncleGusMod transitions
fi
if [ -d "categories_UncleGusMod" ]; then
  mv categories categories_base
  mv categories_UncleGusMod categories
fi
if [ -d "sprites_UncleGusMod" ]; then
  mv sprites sprites_base
  mv sprites_UncleGusMod sprites
fi
if [ -d "ground_UncleGusMod" ]; then
  mv ground ground_base
  mv ground_UncleGusMod ground
fi
if [ -d "animations_UncleGusMod" ]; then
  mv animations animations_base
  mv animations_UncleGusMod animations
fi
if [ -f "dataVersionNumber_UncleGusMod.txt" ]; then
  mv dataVersionNumber.txt dataVersionNumber_base.txt
  mv dataVersionNumber_UncleGusMod.txt dataVersionNumber.txt
fi
if [ -f "settings/useCustomServer_UncleGusMod.ini" ]; then
  mv settings/useCustomServer.ini settings/useCustomServer_base.ini
  mv settings/useCustomServer_UncleGusMod.ini settings/useCustomServer.ini
fi
if [ -f "settings/customServerAddress_UncleGusMod.ini" ]; then
  mv settings/customServerAddress.ini settings/customServerAddress_base.ini
  mv settings/customServerAddress_UncleGusMod.ini settings/customServerAddress.ini
fi
if [ -f "settings/customServerPort_UncleGusMod.ini" ]; then
  mv settings/customServerPort.ini settings/customServerPort_base.ini
  mv settings/customServerPort_UncleGusMod.ini settings/customServerPort.ini
fi