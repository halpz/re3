#include "common.h"
#include "patcher.h"
#include "FileMgr.h"
#include "Directory.h"

CDirectory::CDirectory(int32 maxEntries)
 : numEntries(0), maxEntries(maxEntries)
{
	entries = new DirectoryInfo[maxEntries];
}

CDirectory::~CDirectory(void)
{
	delete[] entries;
}

void
CDirectory::ReadDirFile(const char *filename)
{
	int fd;
	DirectoryInfo dirinfo;

	fd = CFileMgr::OpenFile(filename, "rb");
	while(CFileMgr::Read(fd, (char*)&dirinfo, sizeof(dirinfo)))
		AddItem(dirinfo);
	return CFileMgr::CloseFile(fd);
}

bool
CDirectory::WriteDirFile(const char *filename)
{
	int fd, n;
	fd = CFileMgr::OpenFileForWriting(filename);
	n = CFileMgr::Write(fd, (char*)entries, numEntries*sizeof(DirectoryInfo));
	CFileMgr::CloseFile(fd);
	return n == numEntries*sizeof(DirectoryInfo);
}

void
CDirectory::AddItem(const DirectoryInfo &dirinfo)
{
	assert(numEntries < maxEntries);
	entries[numEntries++] = dirinfo;
}

bool
CDirectory::FindItem(const char *name, uint32 &offset, uint32 &size)
{
	int i;

	for(i = 0; i < numEntries; i++)
		if(strcmpi(entries[i].name, name) == 0){
			offset = entries[i].offset;
			size = entries[i].size;
			return true;
		}
	return false;
}

STARTPATCHES
	InjectHook(0x473630, &CDirectory::ReadDirFile, PATCH_JUMP);
	InjectHook(0x473690, &CDirectory::WriteDirFile, PATCH_JUMP);
	InjectHook(0x473600, &CDirectory::AddItem, PATCH_JUMP);
	InjectHook(0x4736E0, &CDirectory::FindItem, PATCH_JUMP);
ENDPATCHES
