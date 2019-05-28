
#include "stdafx.h"
#include "PipeServerDemo.h"
#include "ServerPipe.h"

int _tmain(int argc, _TCHAR* argv[])
{
//     TestPipeServer();
//     return 0;

    ServerPipe svePipe("\\\\.", "FishingPipe");
    svePipe.AsyncListenPipe();

    return 0;

}

