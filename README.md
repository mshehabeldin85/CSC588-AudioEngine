# Audio Engine
Building an Audio Engine using Microsoft XAudio2 library by applying Muti-Threadibg concepts, command pattern in circular queues to pass commands between threads.

# Demos
This [Youtube Demos Playlist](https://www.youtube.com/playlist?list=PLiPAB5oCbbf8cbWEYzPHaxj6MsrC0gHf7) explains how the engine components are implemented iteratively until achieving the final product.

# Features
1. Asynchronous loading and caching audio sounds.
2. Stitching mutiple audio buffers using voice callbacks.
3. Providing attribute for change volume and panning a sound within the play command.
4. Using handles to control the access of the sound objects between threads.
5. Control sounds through a priority table.
6. Play a list sounds using callbacks.
