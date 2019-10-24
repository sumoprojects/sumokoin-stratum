# sumokoin-stratum

High performance CryptoNote mining stratum with Web-interface written in Golang.

**Stratum feature list:**

* Be your own pool
* Rigs availability monitoring
* Keep track of accepts, rejects, blocks stats
* Easy detection of sick rigs
* Daemon failover list
* Concurrent shares processing
* Beautiful Web-interface

![](https://cdn.pbrd.co/images/jRU3qJj83.png)

## Installation

Dependencies:

  * go-1.6
  * Everything required to build Sumokoin
  * Sumokoin source

### Linux

Use Ubuntu 16.04 LTS.

Compile Sumokoin source (with shared libraries option):

    sudo apt update && sudo apt install build-essential cmake pkg-config libboost-all-dev libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind8-dev liblzma-dev libreadline6-dev libldns-dev libexpat1-dev doxygen graphviz libpgm-dev qttools5-dev-tools libhidapi-dev libusb-dev libprotobuf-dev protobuf-compiler
    git clone https://github.com/sumoprojects/sumokoin.git
    cd sumokoin
    cmake -DBUILD_SHARED_LIBS=1 .
    make
    (There is currently a bug waiting to be fixed at Monero, if it doesnt build with that flag please apply this closed pull of XMR https://github.com/monero-project/monero/pull/5938/files )
Install Golang and required packages:

    sudo apt-get install golang

Clone stratum:

    git clone https://github.com/sumoprojects/sumokoin-stratum.git
    cd sumokoin-stratum

Build stratum:

    MONERO_DIR=/path/to/sumokoin cmake .
    make

`MONERO_DIR=/path/to/sumokoin` is optional, not needed if both `sumokoin` and `sumokoin-stratum` is in the same directory like `/opt/src/`. By default make will search for monero libraries in `../sumokoin`. You can just run `cmake .`.

### Mac OS X

Compile Sumokoin source:

    git clone https://github.com/sumoprojects/sumokoin-stratum.git
    cd monero
    cmake .
    make

Install Golang and required packages:

    brew update && brew install go

Clone stratum:

    git clone https://github.com/sumoprojects/sumokoin-stratum.git
    cd sumokoin-stratum

Build stratum:

    MONERO_DIR=/path/to/sumokoin cmake .
    make

### Running Stratum

    ./build/bin/sumokoin-stratum config.json

If you need to bind to privileged ports and don't want to run from `root`:

    sudo apt-get install libcap2-bin
    sudo setcap 'cap_net_bind_service=+ep' /path/to/sumokoin-stratum

## Configuration

Configuration is self-describing, just copy *config.example.json* to *config.json* and run stratum with path to config file as 1st argument.

```javascript
{
  // Address for block rewards
  "address": "YOUR-ADDRESS-NOT-EXCHANGE",
  // Don't validate address
  "bypassAddressValidation": true,
  // Don't validate shares
  "bypassShareValidation": true,

  "threads": 2,

  "estimationWindow": "15m",
  "luckWindow": "24h",
  "largeLuckWindow": "72h",

  // Interval to poll daemon for new jobs
  "blockRefreshInterval": "1s",

  "stratum": {
    // Socket timeout
    "timeout": "15m",

    "listen": [
      {
        "host": "0.0.0.0",
        "port": 1111,
        "diff": 5000,
        "maxConn": 32768
      },
      {
        "host": "0.0.0.0",
        "port": 3333,
        "diff": 10000,
        "maxConn": 32768
      }
    ]
  },

  "frontend": {
    "enabled": true,
    "listen": "0.0.0.0:8082",
    "login": "admin",
    "password": "",
    "hideIP": false
  },

  "upstreamCheckInterval": "5s",

  "upstream": [
    {
      "name": "Main",
      "host": "127.0.0.1",
      "port": 18081,
      "timeout": "10s"
    }
  ]
}
```

You must use `anything.WorkerID` as username in your miner. Either disable address validation or use `<address>.WorkerID` as username. If there is no workerID specified your rig stats will be merged under `0` worker. If mining software contains dev fee rounds its stats will usually appear under `0` worker. This stratum acts like your own pool, the only exception is that you will get rewarded only after block found, shares only used for stats.

### License

Released under the GNU General Public License v2.

http://www.gnu.org/licenses/gpl-2.0.html
