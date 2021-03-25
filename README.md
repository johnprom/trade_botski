
## The Botski Trading Project
##### Made in Partnership with Questia | Powered by Fossil Fuel

#### Project Propositions

- link coinbase API
- create realtime visual crytpo monitor
- create a user login
- add user "wallet"
- add "trading" capabilties
- add functionality for routine trades/ trade bot capabilities

#### Build Project | Requirements 
- Python 3
- cmake (pip install cmake)
- conan (pip install conan)

#### Build Project | How to Run

> conan install . --install-folder build --build missing

> conan build . --build-folder build --install-folder build

> .\build\bin\BotskiTrading.exe

> conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

> conan profile update settings.cppstd=17 default

> conan install .