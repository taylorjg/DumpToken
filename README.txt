
I wrote a library of code that exhaustively dumps out all available information
for a given token handle i.e. all classes of information available via
GetTokenInformation(). Initially, I used this library to dump out the process
token. I then extended the scope of the project to dump out an impersonation
token. I achieved this by creating a server program which creates an instance
of a small COM object which it registers in the Running Object Table (ROT). A
client program then retrieves a reference to the COM object and invokes a
method on it. This arrangement allowed my to perform some experiments e.g.
running the two programs under different identities and trying different COM
security settings (such as the authentication level and impersonation level).



In order to run the programs, it is necessary to register the COM object and
apply a registry script file, RotServer.reg.

$ regsvr32 <full path to TestObjectSvr.dll>
$ regedit <full path to RotServer.reg>



Some issues arose during development of the project. These are described
below along with details of how I resolved them.

ROTFLAGS_ALLOWANYCLIENT Fails With Error Code 0x80004015
--------------------------------------------------------

Registering the COM object in the ROT with the ROTFLAGS_ALLOWANYCLIENT flag
failed with error code 0x80004015 ("The class is configured to run as a
security id different from the caller"). I resolved this by creating
registry entries for RotServer.exe underneath HKCR\AppID (see RotServer.reg).

LookupAccountSid() and LookupPrivilegeName() and ERROR_ACCESS_DENIED
--------------------------------------------------------------------

I found that calls to these two Win32 functions failed whilst impersonating.
I resolved this by reverting to self and re-impersonating around calls these
functions.

TokenHasRestrictions Is 1 byte Not A DWORD
------------------------------------------

This GetTokenInformation() class is documented as  being a DWORD but in
practice, it appears to be a single byte.

Some GetTokenInformation() Classes Fail With ERROR_BAD_LENGTH
-------------------------------------------------------------

I have a helper function that makes two calls to GetTokenInformation() for a
given class of information – once to determine the size of the buffer and a
second time to retrieve the data. A callback function then dumps the
information – I have a handler function for each class of information.

This works fine for most classes. However, this does not work for four
particular classes because the first call to GetTokenInformation() fails
with ERROR_BAD_LENGTH instead of ERROR_INSUFFICIENT_BUFFER. In addition,
the function does not return the required buffer size. All four of these
classes are documented as being a DWORD. Therefore, I resolved this problem
by hardcoding the buffer size to the size of a DWORD for these four classes.
The four classes are as follows :-

•	TokenSessionId
•	TokenSandBoxInert
•	TokenLinkedToken
•	TokenElevation

