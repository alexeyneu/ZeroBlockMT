 - Sys Req:  
Visual C++ 2013 redist
https://www.microsoft.com/en-us/download/details.aspx?id=40784
openssl
Req: `.lib` out of openssl build  
SSE3 tech
  https://github.com/openssl/openssl/tree/master/include  
https://github.com/pocoproject/openssl/tree/develop/build/win64/bin/release  

  
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

nmake holds well on non-2013
 - ms visual studio 2013 (C++)
32/64-bit : conf manager/change active solution platform  
 - msbuild  
VS2013 x64 Native Tools Command Prompt
```
msbuild  tool3.sln /property:Configuration=Release   /property:Platform=x64

msbuild  tool3.sln \
/property:Configuration=Release   /property:Platform=Win32
```
- nmake  
  
VS2013 x64 Native Tools Command Prompt (standard command prompt works too if env tuned right )
```
cd tool3
nmake
```

