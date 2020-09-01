# CSC588 Audio Engine
Building an Audio Engine using Microsoft XAudio2 library by appliying Muti-Threadibg concepts, command pattern in circular queues to pass commands between threads.

# Features:
1. Asynchronous loading and caching audio sounds.
2. Stitching mutiple audio buffers usin voice callbacks.
3. Providing attribute for change volume and panning a sound within the play command.
4. Using handles to control the access of the sound objects between threads.
5. Contorl sounds through a priority table.
6. Play a list sounds using callbacks.
