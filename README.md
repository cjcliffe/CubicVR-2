CubicVR-2
=========

A 3D engine for iOS/Mac/Linux/Windows/Android/Dreamcast/PSP 

Successor to the 2003-2013 CubicVR C++ engine, with CubicVR.js interoperability.  

"10th anniversary edition"

=========

CubicVR 2 hopes to address a large number of integration issues that arose through adding support for various platforms and OpenGL versions through the years.

Initial support will be focused on utilizing OpenGL ES 2.0 rendering pipeline and shader system design from CubicVR.js with supporting code from existing CubicVR C++ codebase.

Initial target platform will be Mac and iOS and expand to Linux and Windows.  Maintaining interoperability with CubicVR.js formats will be an important goal.

Dreamcast and PSP support will no longer be emulated using OpenGL wrappers for their respective platforms.  Rendering pipelines for these platforms will be built using native pspgu and pvr libraries and have alternate build options for optimal limited memory usage; additional platforms may be possible.

Native toolsets and formats will no longer be a primary goal as before; open source tools and formats such as Blender and COLLADA will be the focus for importing content.  

CubicVR's existing DataTree will be used more extensivly to provide 1-1 translation and interchangability of XML, JSON, Native Binary and Compressed Binaries (FastLZ).
