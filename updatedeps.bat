@REM @echo off

pushd .\Source\Dependencies\

pushd .\Dvaarpaal\
git pull
pushd .\Source\Dependencies\Panshilar\
git pull
popd
popd

pushd .\Muzent\
git pull
pushd .\Source\Dependencies\Panshilar\
git pull
popd
popd

pushd .\Panshilar\
git pull
popd

popd
