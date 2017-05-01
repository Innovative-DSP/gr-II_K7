This GNU Radio out-of-tree (OOT) module has been tested on ePC-K7 and mini-K7 
products running Ubuntu 16.04 with FMC-250 and FMC-310 boards from Innovative 
Integration. GP-DSP firmware from Innovative Integration must be installed on 
the K7 to support this module.

Innovative Integration Digital Transceiver Instrumentation Series:  
https://www.innovative-dsp.com/products.php?product=Digital-Transceiver-Overview

See you at the next GNU Radio Conference!

### Current Blocks

* II DDC Source (digital down-converter)
* II FFT Source (FFT of DDC data)
* II DUC Sink (digital up-converter)

### Installation

```
# Update the package list and upgrade all your system software to the latest 
# version available:
sudo apt-get update && sudo apt-get -y upgrade

# Install pip:
sudo apt-get install python-pip
sudo -H pip install --upgrade pip

# Install pybombs:
sudo -H pip install pybombs

# Install recipes:
pybombs recipes add gr-recipes git+https://github.com/gnuradio/gr-recipes.git
pybombs recipes add gr-etcetera git+https://github.com/gnuradio/gr-etcetera.git

# Make installation directory, e.g., GRinstall:
mkdir GRinstall/

# Install gnuradio and dependencies (substituting user name):
pybombs prefix init /home/[user]/GRinstall/ -a default -R gnuradio-default

# Copy the recipe for the II K7 OOT blocks (provided) to a location where 
# pybombs can find it, e.g., the ~/.pybombs/recipes/ directory:
cp gr-II_K7.lwr ~/.pybombs/recipes/

# Install OOT modules:
pybombs install gr-II_K7

# Edit .bashrc to run software in custom prefix:
gedit ~/.bashrc

# Add the line below to the end of .bashrc:
source ~/GRinstall/setup_env.sh

# In a new terminal window, run GNU Radio Companion:
gnuradio-companion

# In GNU Radio Companion's block selection pane, collapse the "Core" category
# of blocks or scroll down past it to see the "II K7" category listed below it.
```
