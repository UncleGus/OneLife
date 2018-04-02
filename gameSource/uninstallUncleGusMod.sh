if [ -d "objects_base" ]; then
  mv objects objects_UncleGusMod
  mv objects_base objects
fi
if [ -d "transitions_base" ]; then
  mv transitions transitions_UncleGusMod
  mv transitions_base transitions
fi
if [ -d "categories_base" ]; then
  mv categories categories_UncleGusMod
  mv categories_base categories
fi
if [ -f "dataVersionNumber_base.txt" ]; then
  mv dataVersionNumber.txt dataVersionNumber_UncleGusMod.txt
  mv dataVersionNumber_base.txt dataVersionNumber.txt
fi
if [ -f "settings/useCustomServer_base.ini" ]; then
  mv settings/useCustomServer.ini settings/useCustomServer_UncleGusMod.ini
  mv settings/useCustomServer_base.ini settings/useCustomServer.ini
fi
if [ -f "settings/customServerAddress_base.ini" ]; then
  mv settings/customServerAddress.ini settings/customServerAddress_UncleGusMod.ini
  mv settings/customServerAddress_base.ini settings/customServerAddress.ini
fi
if [ -f "settings/customServerPort_base.ini" ]; then
  mv settings/customServerPort.ini settings/customServerPort_UncleGusMod.ini
  mv settings/customServerPort_base.ini settings/customServerPort.ini
fi