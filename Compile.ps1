if ((Test-Path "./build/") -eq 0)
{
    mkdir build
}
$target="Matrix-Calculator.exe"

cd build

taskkill /IM $target /F

cmake ..
cmake --build .
