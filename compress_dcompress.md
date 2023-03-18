A time traveler got stuck in the past in the dinosaur era — that was the first
human who travelled through time. Unfortunately, the engineers working on the
time machine made a mistake and the time traveler had barely survived during his
journey. Due to the issue, it’s impossible for the poor man to get back. At the
same time, nobody wants to risk and use a similar time machine to make a trip to
the past in order to bring that person back before the problem is fixed.
The time traveler noticed that the time machine produced a lot of logs on the
disk
which may help the engineers with fixing the issue, in both textual and binary
formats.
In addition, he’s noticed, that most of the files are of the same size, and some
log files are binary identical to each other even though they are located in
different
folders and have different names. He was able to report this information to the
nowadays
engineers. It turns out, that the time machine is still capable to receive a
single console application written in C++ (with additional libraries if needed),
and to send only one file with data back. Nevertheless, it’s running out of
power, therefore the application must be effective, and the data size should be
as minimal as possible.
Please help the time traveler to send the logs to the engineers and make such
console application, which will be able

    • to go through the file structure (with subfolders) starting from a specified folder
    • produce a single file with the content of the folder (in an effective way in term of both the
    resource usage and produced file’s size).
    • to “unpack” the produced file to the exactly the same folders/files structure and content which
    was given to the application as an original input. You may assume that:
    • each file size doesn’t exceed 2Gb
    • the number of files doesn’t exceed 1048576
    • the disk capacity in the time machine is sufficient to at least make a copy of the whole logs folder.

The time traveler is starving and in a dangerous situation. So, hurry up!