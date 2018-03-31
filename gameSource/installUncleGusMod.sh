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
if [ -f "dataVersionNumber_UncleGusMod.txt" ]; then
  mv dataVersionNumber.txt dataVersionNumber_base.txt
  mv dataVersionNumber_UncleGusMod.txt dataVersionNumber.txt
fi
if [ -f "settings/useCustomServer_UncleGusMod.ini" ]; then
  mv settings/useCustomServer.ini settings/useCustomServer_base.ini
  mv settings/useCustomServer_UncleGusMod.ini settings/useCustomServer.ini
fi
if [ -f "settings/customServerAddress_UncleGusMod.ini" ]; then
  mv settings/customServerAddress.ini settings/CustomServerAddress_base.ini
  mv settings/customServerAddress_UncleGusMod.ini settings/CustomServerAddress.ini
fi
if [ -f "settings/customServerPort_UncleGusMod.ini" ]; then
  mv settings/customServerPort.ini settings/customServerPort_base.ini
  mv settings/customServerPort_UncleGusMod.ini settings/customServerPort.ini
fi