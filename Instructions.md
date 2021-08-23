# Prerequisites
Opticks requires Geant4 (10.7.p02), nvidia cuda (11.3)  and nvidia Optix (6.5) among other libraries. CaTS in addition will require ROOT. If all these are available on your machine skip directly to 
(**Building opticks vs. existing libraries**). On a 'blank' computing system it makes sense to build CLHEP then Geant4 and finally ROOT assuring that all the necessary development libraries and headers are installed. 
# Building CLHEP
The current version of Geant4 10.07.p02 is build on clhep 2.4.4.0. 
CLHEP can be found at:
https://proj-clhep.web.cern.ch/proj-clhep/clhep23.html

to build it from scratch using cmake (used cmake version 3.20.5) 

    cd to the directory where you want to build clhep
    wget https://proj-clhep.web.cern.ch/proj-clhep/dist1/clhep-2.4.4.0.tgz
    tar xzvf clhep-2.4.4.0.tgz
    cd 2.4.4.0/
    mkdir CLHEP-build
    cd  CLHEP-build
    cmake -DCMAKE_INSTALL_PREFIX=../CLHEP-install DCLHEP_BUILD_CXXSTD=-std=c++11 ../CLHEP
    make -j 8
    make install

**Note** the default install directory is /usr/local but one needs root privileges to install it there

# Building Geant4

Geant4 versions are available at:
https://geant4.web.cern.ch/support/download


    cd to the directory where you want to install Geant4
    wget https://geant4-data.web.cern.ch/releases/geant4.10.07.p02.tar.gz
    mkdir geant4.10.07.p02-build
    cd  geant4.10.07.p02-build
    cmake -DCMAKE_INSTALL_PREFIX=../geant4.10.07.p02-install -DGEANT4_BUILD_VERBOSE_CODE=OFF -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_SYSTEM_CLHEP=ON -DGEANT4_USE_GDML=ON -DGEANT4_USE_SYSTEM_EXPAT=ON -DGEANT4_USE_SYSTEM_ZLIB=ON  -DGEANT4_USE_QT=ON -DGEANT4_BUILD_MULTITHREADED=ON -DGEANT4_USE_OPENGL_X11=ON ../geant4.10.07.p02
    make -j 8
    make install

check the output for any error install any development packages that might be necessary. 
other Geant4 versions are available at:
https://geant4.web.cern.ch/support/download



# Building ROOT 

check the output for any error install any development packages that might be necessary. 



# Installing CUDA

cuda (11.3) is available at the NVIDIA web site just follow the instruction depending on the system you are using. 

https://developer.nvidia.com/cuda-downloads

**Note** this will also install the corresponding NVIDIA graphics driver.  

Another way to obtain cuda is to install the NVIDIA hpc-sdk kit. Which can be found here. 
https://developer.nvidia.com/nvidia-hpc-sdk-downloads

The NVIDIA hpc-sdk kit provides an interesting set of tools e.g. nvc++ which allows offloading of parallel algorithms to NVIDIA GPUs.

# Installing Optix (6.5)

https://developer.nvidia.com/designworks/optix/download



# Building opticks vs. existing libraries

This are instructions how to build opticks making use of preinstalled libraries available on the system. These libraries include CLHEP, xerces-c, boost and  Geant4.
For geant 4 we use the current version at the time of writing which is Geant4.10.7.p2. We make use of the fact that the om-cmake function of om.bash is sensitive
to CMAKE_PREFIX_PATH envvar so that we can point to the directories where the libraries are installed and void having to rebuild them.  In principle just cut and paste the following line to a file change the envars of the different directories to match your system and source the resulting script.

    cat > setup_opticks.sh << +EOF
    export WORK_DIR=/data2/wenzel/gputest_10.7.p02
    export OptiX_INSTALL_DIR=/home/wenzel/NVIDIA-OptiX-SDK-6.5.0-linux64
    export OPTICKS_COMPUTE_CAPABILITY=75
    export CUDA_INSTALL_DIR=/usr/local/cuda-11.3
    export CUDA_SAMPLES=${CUDA_INSTALL_DIR}/samples
    export G4INSTALL=/data2/wenzel/Geant4.10.07.p02_install
    . ${G4INSTALL}/bin/Geant4.sh
    . /data2/wenzel/root_install/bin/thisroot.sh
    export LOCAL_BASE=${WORK_DIR}/local
    export CMAKE_PREFIX_PATH=${G4INSTALL}:${LOCAL_BASE}/opticks/externals:${OptiX_INSTALL_DIR}:${WORK_DIR}/opticks/cmake/Modules/:${WORK_DIR}/local/opticks:${WORK_DIR}/local/opticks:${WORK_DIR}/local/opticks/externals/
    export PYTHONPATH=$WORK_DIR
    export OPTICKS_HOME=${WORK_DIR}/opticks
    export PATH=${LOCAL_BASE}/bin:${PATH}
    export OPTICKS_PREFIX=${WORK_DIR}/local/opticks                            
    export OPTICKS_INSTALL_PREFIX=$LOCAL_BASE/opticks
    export OPTICKS_OPTIX_PREFIX=/home/wenzel/NVIDIA-OptiX-SDK-6.5.0-linux64/
    export OPTICKS_CUDA_PREFIX=${CUDA_INSTALL_DIR}
    export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--rngmax 10 --rtx 1"
    opticks-(){ . ${OPTICKS_HOME}/opticks.bash && opticks-env $* ; }
    op(){ op.sh $* ; }
    o(){ cd $(opticks-home) ; hg st ; }
    # make sure to add the compiler options
    new=" -fPIC" 
    case ":${CXXFLAGS:=$new}:" in
        *:"$new":*)  ;;
        *) CXXFLAGS="$CXXFLAGS:$new"  ;;
    esac
    new=" -fPIC" 
    case ":${CFLAGS:=$new}:" in
        *:"$new":*)  ;;
        *) CFLAGS="$CFLAGS:$new"  ;;
    esac
    # speed up the make process
    new=" -j$(($(grep -c ^processor /proc/cpuinfo) - 1))" 
    case ":${MAKEFLAGS:=$new}:" in
        *:"$new":*)  ;;
        *) MAKEFLAGS="$MAKEFLAGS:$new"  ;;
    esac
    # deal with the $LD_LIBRARYPATH
    new=${OptiX_INSTALL_DIR}/lib64/
    case ":${LD_LIBRARY_PATH:=$new}:" in
        *:"$new":*)  ;;
        *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
    esac
    new=${OPTICKS_HOME}/externals/lib
    case ":${LD_LIBRARY_PATH:=$new}:" in
        *:"$new":*)  ;;
        *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
    esac
    new=${CUDA_INSTALL_DIR}/lib64/
    case ":${LD_LIBRARY_PATH:=$new}:" in
        *:"$new":*)  ;;
        *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
    esac
    new=${LOCAL_BASE}/opticks/lib/
    case ":${LD_LIBRARY_PATH:=$new}:" in
        *:"$new":*)  ;;
        *) LD_LIBRARY_PATH="$new:$LD_LIBRARY_PATH"  ;;
    esac
    opticks-
    new=${CUDA_INSTALL_DIR}/bin
    case ":${PATH:=$new}:" in
        *:"$new":*)  ;;
        *) PATH="$new:$PATH"  ;;
    esac
    #new=${CUDA_INSTALL_DIR}/NsightCompute-2019.3
    #case ":${PATH:=$new}:" in
    #    *:"$new":*)  ;;
    #    *) PATH="$new:$PATH"  ;;
    #esac
    new=${OPTICKS_HOME}/bin/
    case ":${PATH:=$new}:" in
        *:"$new":*)  ;;
        *) PATH="$new:$PATH"  ;;
    esac
    new=${OPTICKS_HOME}/ana/
    case ":${PATH:=$new}:" in
        *:"$new":*)  ;;
        *) PATH="$new:$PATH"  ;;
    esac
    new=${LOCAL_BASE}/opticks/lib/
    case ":${PATH:=$new}:" in
        *:"$new":*)  ;;
        *) PATH="$new:$PATH"  ;;
    esac
    new=${CUDA_SAMPLES}/bin/x86_64/linux/release/
    case ":${PATH:=$new}:" in
        *:"$new":*)  ;;
        *) PATH="$new:$PATH"  ;;
    esac
    oinfo-(){
        echo 'LD_LIBRARY_PATH:';
        echo '================';
        echo  ${LD_LIBRARY_PATH}| tr : \\n;
        echo;
        echo 'PATH:';
        echo '=====';
        echo  ${PATH}| tr : \\n;
        echo;
        echo 'CMAKE_PREFIX_PATH:';
        echo '==================';
        echo  ${CMAKE_PREFIX_PATH}| tr : \\n;
        }
    dinfo-(){    
        nvidia-smi;
        ${CUDA_SAMPLES}/bin/x86_64/linux/release/deviceQuery
    }
    export OPTICKS_KEY=CaTS.X4PhysicalVolume.World_PV.8bf2e3a1e2eb9062d0d6b8a2a45c4cf3
    +EOF

    source setup_opticks.sh
    oinfo-
    dinfo-
    mkdir -p ${WORK_DIR}/local/opticks/externals/
    cd ${WORK_DIR}/local/opticks/externals/
    ln -s ${OptiX_INSTALL_DIR} OptiX
    cd ${WORK_DIR}
    opticks-externals-install >& install_ext.log &
    cd ${WORK_DIR}
    echo $G4INSTALL
    opticks-full  >& install_full.log &
    opticks-t
    #cd ${OPTICKS_HOME}/externals
    #opticksdata-
    #opticksdata--
    #geocache-
    #geocache-create- --gdmlpath  ${WORK_DIR}/local/opticks/opticksdata/export/juno1808/g4_00.gdml
    #export OPTICKS_KEY=OKX4Test.X4PhysicalVolume.lWorld0x4bc2710_PV.6c0b1c7e48b32eb1d3eb898e06ad0a33
    #opticks-t
    



https://bitbucket.org/simoncblyth/opticks.git.

The components of CaTS are:


Detector Description:      described in gdml input file (e.g. crystalcal.gdml)
(Geometry, Materials,
 optical properties,
 sensitive detector)

Input modules:                

    GPS
    Particle Gun
    HEPMC (Pythia)


Physics Lists:                  choice of all Reference Physics Lists
                                          optical physics processes (Cerenkov, Rayleigh,
                                          Scintillation etc.) are added (talk to)  
                
Sensitive Detectors:        (+ corresponding Hit classes)        

    TrackerSD(Hit)  
    CalorimeterSD(Hit)
    DRCalorimeterSD(Hit) (besides registering energy deposit counts produced Cerenkov photons)
    StoppingCalorimeterSD (registers total energy of entering particle and kills the particle afterwards to avoid further tracking)
    PhotonSD(Hit): sensitive detector that  registers optical photons.





This requires the opticks environment to be set up properly.  At the moment we
use the following external packages and versions thereof:  

- nvidia Optix 6.5
- nvidia cuda 11.0
- nvidia driver 460.27.04
- Geant4 10.7.p02
- xercesc 3.2.2
- openmesh 6.3
- glew 1.13.0
- glfw 3.1.1
- cmake 3.18.4
- ROOT 6.22/06

To get started : 

```bash
git clone https://github.com/hanswenzel/CaTS.git
cd CaTS/

# now have a look at set_env_lq.sh and change the variables on the top to point to the opticks installation you want to use and change it accordingly.
# The provided set_env_lq.sh gives an example.
# After you changed it:

cp set_env_lq.sh set_env.sh
source setup_opticks.sh 
cd ../
mkdir CaTS-build
cd CaTS-build

cmake -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_PREFIX_PATH="${LOCAL_BASE}/opticks/externals;${LOCAL_BASE}/opticks" \
  -DOPTICKS_PREFIX=${LOCAL_BASE}/opticks \
  -DCMAKE_MODULE_PATH=${OPTICKS_HOME}/cmake/Modules \
  -DCMAKE_INSTALL_PREFIX=../CaTS-install \
  ../CaTS




make install
cd ../CaTS-install/bin
export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="--rngmax 10 --rtx 1"
time ./CaTS -g  simpleLArTPC.gdml -pl 'FTFP_BERT+OPTICAL+STEPLIMIT'  -macro time.mac

Only the -g command line variable is mandatory! If you don't specify the macro file interactive mode is assumed:

./CaTS -g simpleLArTPC.gdml -pl 'FTFP_BERT+OPTICAL+STEPLIMIT'

if you don't provide the -pl argument the default physics list configuration:
'FTFP_BERT+OPTICAL+STEPLIMIT'
is used

```
![alt text](https://github.com/hanswenzel/CaTS/blob/master/images/display.png)
```bash
to look at the hit collection and make a few histograms:

./readHits  NewHits_Run0.root histos.root

on can the use root to look  at the plots:

root histos.root
   ------------------------------------------------------------------
  | Welcome to ROOT 6.22/06                        https://root.cern |
  | (c) 1995-2020, The ROOT Team; conception: R. Brun, F. Rademakers |
  | Built for linuxx8664gcc on Dec 13 2020, 13:28:00                 |
  | From tags/v6-22-06@v6-22-06                                      |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q'       |
   ------------------------------------------------------------------

root [0] 
Attaching file histos.root as _file0...
(TFile *) 0x559578f76f60
root [1] TBrowser b
(TBrowser &) Name: Browser Title: ROOT Object Browser
```

![alt text](https://github.com/hanswenzel/CaTS/blob/master/images/position.png)

