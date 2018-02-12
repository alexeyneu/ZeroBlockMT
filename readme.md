 - Sys Req:  
Visual C++ 2010 redist 
https://www.microsoft.com/en-us/download/details.aspx?id=14632  
and openssl   
![Screen1](/screens/Untitled%201.jpg)
## about 
 mines block that starts blockchain.  
 all options are in `MainFrm.h`  
## build:
nmake holds well on non-2010  
 - ms visual studio 2010 (C++)  
32/64-bit : conf manager/change active solution platform  
 - msbuild  
vs command prompt(2010)
```
msbuild  tool3.sln /property:Configuration=Release   /property:Platform=x64

msbuild  tool3.sln \
/property:Configuration=Release   /property:Platform=Win32
```
- nmake  
  
vs win64 command prompt (standard command prompt works too if env tuned right ) 
```
cd tool3
nmake
```

