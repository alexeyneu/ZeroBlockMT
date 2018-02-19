 - Sys Req:  
Visual C++ 2010 redist 
https://www.microsoft.com/en-us/download/details.aspx?id=14632  
[![version](https://img.shields.io/github/downloads/alexeyneu/ZeroBlockMT/total.svg?style=plastic)](https://github.com/alexeyneu/ZeroBlockMT/tree/master/x64/Release)  
![Screen1](/screens/Untitled%201.jpg)
![Screen1](/screens/Untitled%202.jpg)
![Screen1](/screens/Untitled%208.jpg)
## about 
 mines block that starts blockchain.  
where are these tools were used?  
https://github.com/DMDcoin/Diamond/blob/a1a7f6b8a3bad0df8fd8ddb9ead0347b1fa440f4/src/chainparams.cpp#L125  
i.e. .One used there is not mine.
## build:  
Req: `.lib` out of openssl build 
  
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

