#include "../../lib/ff14b/source/ff.h"
#include "diskio.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM     0
#define DEV_FLASH   1

/*
 * My implementation
 */
#include "posix/ram_disk.h"

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
  BYTE pdrv    /* Physical drive nmuber to identify the drive */
)
{
  switch (pdrv) {
  case DEV_RAM :
    DSTATUS stat = RAM_disk_status();
    return stat;
  case DEV_FLASH :
    return STA_NOINIT;
  }
  return STA_NOINIT;
}


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
  BYTE pdrv        /* Physical drive nmuber to identify the drive */
)
{
  switch (pdrv) {
  case DEV_RAM :
    DSTATUS stat = RAM_disk_initialize();
    return stat;
  case DEV_FLASH :
    return STA_NOINIT;
  }
  return STA_NOINIT;
}


/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
  BYTE pdrv,    /* Physical drive nmuber to identify the drive */
  BYTE *buff,    /* Data buffer to store read data */
  LBA_t sector,  /* Start sector in LBA */
  UINT count    /* Number of sectors to read */
)
{
  DRESULT res = RES_NOTRDY;

  switch (pdrv) {
  case DEV_RAM :
    res = RAM_disk_read(buff, sector, count);
    return res;
  case DEV_FLASH :
    return res;
  }
  return RES_PARERR;
}


/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
  BYTE pdrv,      /* Physical drive nmuber to identify the drive */
  const BYTE *buff,  /* Data to be written */
  LBA_t sector,    /* Start sector in LBA */
  UINT count      /* Number of sectors to write */
)
{
  DRESULT res = RES_NOTRDY;

  switch (pdrv) {
  case DEV_RAM :
    res = RAM_disk_write(buff, sector, count);
    return res;
  case DEV_FLASH :
    return res;
  }
  return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
  BYTE pdrv,    /* Physical drive nmuber (0..) */
  BYTE cmd,    /* Control code */
  void *buff    /* Buffer to send/receive control data */
)
{

  DRESULT res = RES_NOTRDY;
  switch (pdrv) {
  case DEV_RAM :
    return RAM_disk_ioctl(cmd, (int *)buff);
  case DEV_FLASH :
    return res;
  }
  return RES_PARERR;
}

