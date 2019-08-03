//############################################################################
//##                                                                        ##
//##  Miles Sound System                                                    ##
//##                                                                        ##
//##  MSS.H: Miles Sound System main header file                            ##
//##                                                                        ##
//##  Version 1.00 of 15-Feb-95: Initial, derived from AIL.H V3.02          ##
//##          1.01 of 19-Jun-95: Added various functions for V3.03 release  ##
//##          1.02 of 22-Nov-95: C++ typedef problem fixed, declspecs added ##
//##          1.03 of 15-Feb-96: Changes for 16 bit callbacks and multiple  ##
//##                             16 bit DLL loads (JKR)                     ##
//##          1.04 of  2-Nov-97: Changes made to handle DLS in future       ##
//##                             versions                                   ##
//##          1.05 of  1-Jan-98: Massive changes for version 4.0            ##
//##          1.06 of 17-Sep-98: Massive changes for version 5.0            ##
//##          1.07 of  2-Feb-99: Changes for new input API                  ##
//##          1.08 of  8-Feb-99: Changes for new filter helper functions    ##
//##                                                                        ##
//##  Author: John Miles                                                    ##
//##                                                                        ##
//############################################################################
//##                                                                        ##
//##  Contact RAD Game Tools at 425-893-4300 for technical support.         ##
//##                                                                        ##
//############################################################################

#ifndef MSS_VERSION

#define MSS_VERSION      "6.1a"
#define MSS_MAJOR_VERSION 6
#define MSS_MINOR_VERSION 1
#define MSS_SUB_VERSION   1
#define MSS_VERSION_DATE "06-Mar-01"

#define MSS_COPYRIGHT "Copyright (C) 1991-2001, RAD Game Tools, Inc."

#endif

#ifndef MSS_H
#define MSS_H

// IS_DOS for DOS
// IS_WINDOWS for Windows or Win32s
// IS_WIN32 for Win32s
// IS_WIN16 for Windows
// IS_32 for 32-bit DOS or Win32s
// IS_16 for 16-bit Windows
// IS_LE for little endian (PCs)
// IS_BE for big endian (Macs)
// IS_X86 for Intel
// IS_MAC for Mac
// IS_PPC for PPC Mac
// IS_68K for 68K Mac


#ifdef IS_DOS
#undef IS_DOS
#endif

#ifdef IS_WINDOWS
#undef IS_WINDOWS
#endif

#ifdef IS_WIN32
#undef IS_WIN32
#endif

#ifdef IS_WIN16
#undef IS_WIN16
#endif

#ifdef IS_32
#undef IS_32
#endif

#ifdef IS_16
#undef IS_16
#endif

#ifdef IS_LE
#undef IS_LE
#endif

#ifdef IS_BE
#undef IS_BE
#endif

#ifdef IS_X86
#undef IS_X86
#endif

#ifdef IS_MAC
#undef IS_MAC
#endif

#ifdef IS_PPC
#undef IS_PPC
#endif

#ifdef IS_68K
#undef IS_68K
#endif

#ifdef __DOS__
  #define IS_DOS
  #define IS_32
  #define IS_LE
  #define IS_X86
#else
  #ifdef _WIN32
    #define IS_WINDOWS
    #define IS_WIN32
    #define IS_32
    #define IS_LE
    #define IS_X86
  #else
    #ifdef WIN32
      #define IS_WINDOWS
      #define IS_WIN32
      #define IS_32
      #define IS_LE
      #define IS_X86
    #else
      #ifdef __NT__
        #define IS_WINDOWS
        #define IS_WIN32
        #define IS_32
        #define IS_LE
        #define IS_X86
      #else
        #ifdef __WIN32__
          #define IS_WINDOWS
          #define IS_WIN32
          #define IS_32
          #define IS_LE
          #define IS_X86
        #else
          #ifdef _WINDOWS
            #define IS_WINDOWS
            #define IS_WIN16
            #define IS_16
            #define IS_LE
            #define IS_X86
          #else
            #ifdef _WINDLL
              #define IS_WINDOWS
              #define IS_WIN16
              #define IS_16
              #define IS_LE
              #define IS_X86
            #else
              #ifdef WINDOWS
                #define IS_WINDOWS
                #define IS_WIN16
                #define IS_16
                #define IS_LE
                #define IS_X86
              #else
                #ifdef __WINDOWS__
                  #define IS_WINDOWS
                  #define IS_WIN16
                  #define IS_16
                  #define IS_LE
                  #define IS_X86
                #else
                  #ifdef _Windows
                    #define IS_WINDOWS
                    #define IS_WIN16
                    #define IS_16
                    #define IS_LE
                    #define IS_X86
                  #else
                    #if defined(macintosh) || defined(__powerc) || defined(powerc) || defined(__POWERPC__) || defined(__MC68K__)
                      #define IS_MAC
                      #define IS_32
                      #define IS_BE
                      #if defined(__powerc) || defined(powerc) || defined(__POWERPC__)
                        #define IS_PPC
                      #else
                        #if defined(__MC68K__)
                          #define IS_68K
                        #endif
                      #endif
                    #endif
                  #endif
                #endif
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif
#endif

#if (!defined(IS_LE) && !defined(IS_BE))
  #error MSS.H did not detect your platform.  Define __DOS__, _WINDOWS, WIN32, or macintosh.
#endif


#if defined(_PUSHPOP_SUPPORTED) || PRAGMA_STRUCT_PACKPUSH
  #pragma pack(push,1)
#else
  #pragma pack(1)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef IS_DOS

#define AILCALLBACK __pascal
#define AILEXPORT cdecl
#define DXDEC extern
#define DXDEF
#define AILCALL cdecl
#define FAR
#define HIWORD(ptr) (((U32)ptr)>>16)
#define LOWORD(ptr) ((U16)((U32)ptr))

#define FOURCC U32

#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
              ((U32)(U8)(ch0) | ((U32)(U8)(ch1) << 8) |   \
              ((U32)(U8)(ch2) << 16) | ((U32)(U8)(ch3) << 24 ))

#define mmioFOURCC(w,x,y,z) MAKEFOURCC(w,x,y,z)

#define AILLIBCALLBACK __pascal

#define MSS_MAIN_DEF

#define MSS_REDIST_DIR_NAME "DOS"

#define MSS_DIR_SEP "\\"
#define MSS_DIR_UP ".." MSS_DIR_SEP
#define MSS_DIR_UP_TWO MSS_DIR_UP MSS_DIR_UP

#else

#ifdef IS_WINDOWS

#define AILLIBCALLBACK WINAPI

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef WIN32_EXTRA_LEAN
#define WIN32_EXTRA_LEAN
#endif

#ifndef STRICT
#define STRICT
#endif

#include <windows.h>
#include <mmsystem.h>

#define MSS_MAIN_DEF __cdecl

//
// If compiling MSS DLL, use __declspec(dllexport) for both
// declarations and definitions
//
// If compiling MSS16 library or application, use "extern" in declarations
// and nothing in definitions
//

#ifdef IS_WIN32

  #define AILEXPORT WINAPI

  #ifdef BUILD_MSS
    #define DXDEC __declspec(dllexport)
    #define DXDEF __declspec(dllexport)
  #else

    #if 1 /*def __BORLANDC__*/
      #define DXDEC extern
	  #define DXDEF
    #else
      #define DXDEC __declspec(dllimport)
    #endif

  #endif

  #define MSSDLLNAME "MSS32.DLL"
  #define MSS_REDIST_DIR_NAME "WIN32"

  #define MSS_DIR_SEP "\\"
  #define MSS_DIR_UP ".." MSS_DIR_SEP
  #define MSS_DIR_UP_TWO MSS_DIR_UP MSS_DIR_UP
 
#else

  #define AILEXPORT __export WINAPI

  #define DXDEC  extern
  #define DXDEF

  #define MSSDLLNAME "MSS16.DLL"
  #define MSS_REDIST_DIR_NAME "WIN16"
  
  #define MSS_DIR_SEP "\\"
  #define MSS_DIR_UP ".." MSS_DIR_SEP
  #define MSS_DIR_UP_TWO MSS_DIR_UP MSS_DIR_UP

#endif

#define AILCALL WINAPI
#define AILCALLBACK AILEXPORT

typedef LPVOID AILLPDIRECTSOUND;
typedef LPVOID AILLPDIRECTSOUNDBUFFER;

#else

#ifdef IS_MAC

#include <string.h>
#include <Files.h>
#include <Sound.h>
#include <Resources.h>		// needed for GetResource, ReleaseResource

#define FAR

#define AILLIBCALLBACK //pascal
#define AILCALL        //pascal
#define AILEXPORT      //pascal
#define AILCALLBACK    //pascal

#ifdef BUILD_MSS
  #define DXDEC __declspec(export)
  #define DXDEF
#else
  #define DXDEC extern
  #define DXDEF
#endif

#define MSS_REDIST_DIR_NAME "MAC"

#define MSS_DIR_SEP ":"
#define MSS_DIR_UP ":" MSS_DIR_SEP
#define MSS_DIR_UP_TWO MSS_DIR_UP MSS_DIR_SEP

#define HIWORD(ptr) (((U32)ptr)>>16)
#define LOWORD(ptr) ((U16)((U32)ptr))

#define FOURCC U32

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
        (((U32)(U8)(ch0) << 24) | ((U32)(U8)(ch1) << 16) |   \
              ((U32)(U8)(ch2) <<  8) | ((U32)(U8)(ch3)      ))
#endif

#define mmioFOURCC(w,x,y,z) MAKEFOURCC(w,x,y,z)

#define MSS_MAIN_DEF

#endif

#endif

#endif

#ifndef NULL
#define NULL 0
#endif

//
// Misc. constant definitions
//

#define MAX_DRVRS                16       // Max. # of simultaneous drivers
#define MAX_TIMERS               16       // Max. # of simultaneous timers
#define MAX_NOTES                32       // Max # of notes "on"
#define FOR_NEST                 4        // # of nested XMIDI FOR loops
#define NUM_CHANS                16       // # of possible MIDI channels
#define MAX_W_VOICES             16       // Max virtual wave synth voice cnt
#define MAX_W_ENTRIES            512      // 512 wave library entries max.
#ifdef IS_MAC
#define MAX_INSTR                150      // Max # of instruments 128 + 32
#endif

#define MIN_CHAN                 ( 1-1)   // Min channel recognized (0-based)
#define MAX_CHAN                 (16-1)   // Max channel recognized
#define MIN_LOCK_CHAN            ( 2-1)   // Min channel available for locking
#define MAX_LOCK_CHAN            ( 9-1)   // Max channel available for locking
#define PERCUSS_CHAN             (10-1)   // Percussion channel (no locking)

#define AIL_MAX_FILE_HEADER_SIZE 4096     // AIL_set_named_sample_file() requires at least 4K
                                          // of data or the entire file image, whichever is less,
                                          // to determine sample format
#define DIG_F_16BITS_MASK        1
#define DIG_F_STEREO_MASK        2
#define DIG_F_ADPCM_MASK         4

#define DIG_F_MONO_8             0        // PCM data formats
#define DIG_F_MONO_16            (DIG_F_16BITS_MASK)
#define DIG_F_STEREO_8           (DIG_F_STEREO_MASK)
#define DIG_F_STEREO_16          (DIG_F_STEREO_MASK|DIG_F_16BITS_MASK)
#define DIG_F_ADPCM_MONO_16      (DIG_F_ADPCM_MASK |DIG_F_16BITS_MASK)
#define DIG_F_ADPCM_STEREO_16    (DIG_F_ADPCM_MASK |DIG_F_16BITS_MASK|DIG_F_STEREO_MASK)
#define DIG_F_USING_ASI          16

#define DIG_PCM_SIGN             0x0001   // (obsolete)
#define DIG_PCM_ORDER            0x0002

#define DIG_PCM_POLARITY         0x0004   // PCM flags used by driver hardware
#define DIG_PCM_SPLIT            0x0008
#define DIG_BUFFER_SERVICE       0x0010
#define DIG_DUAL_DMA             0x0020
#define DIG_RECORDING_SUPPORTED  0x8000

#define WAVE_FORMAT_PCM         1
#define WAVE_FORMAT_IMA_ADPCM   0x0011

#ifdef IS_DOS

#define AIL3DIG                  0        // .DIG driver
#define AIL3MDI                  1        // .MDI driver

#define DIG_DETECT_8_BIT_ONLY    0x0001   // Detect 8-bit DMA only
#define DIG_DETECT_16_BIT_ONLY   0x0002   // Detect 16-bit DMA only
#define DIG_DETECT_8_AND_16_BITS 0x0003   // Detect both 8- and 16-bit DMA

#define DRV_INIT          0x300     // Functions common to .MDI and .DIG
#define DRV_GET_INFO      0x301     // drivers
#define DRV_SERVE         0x302
#define DRV_PARSE_ENV     0x303
#define DRV_VERIFY_IO     0x304
#define DRV_INIT_DEV      0x305
#define DRV_SHUTDOWN_DEV  0x306

#define DIG_HW_VOLUME     0x400     // .DIG driver functions
#define DIG_START_P_CMD   0x401
#define DIG_STOP_P_REQ    0x402
#define DIG_START_R_CMD   0x403
#define DIG_STOP_R_REQ    0x404
#define DIG_VSE           0x405

#define MDI_HW_VOLUME     0x500     // .MDI driver functions
#define MDI_INIT_INS_MGR  0x501
#define MDI_MIDI_XMIT     0x502
#define MDI_INSTALL_T_SET 0x503
#define MDI_GET_T_STATUS  0x504
#define MDI_PROT_UNPROT_T 0x505
#define MDI_VSE           0x506

#else

//
// Pass to AIL_midiOutOpen for NULL MIDI driver
//

#define MIDI_NULL_DRIVER ((U32)(S32)-2)

#endif


//
// Non-specific XMIDI/MIDI controllers and event types
//

#define SYSEX_BYTE        105
#define PB_RANGE          106
#define CHAN_MUTE         107
#define CALLBACK_PFX      108
#define SEQ_BRANCH        109
#define CHAN_LOCK         110
#define CHAN_PROTECT      111
#define VOICE_PROTECT     112
#define TIMBRE_PROTECT    113
#define PATCH_BANK_SEL    114
#define INDIRECT_C_PFX    115
#define FOR_LOOP          116
#define NEXT_LOOP         117
#define CLEAR_BEAT_BAR    118
#define CALLBACK_TRIG     119
#define SEQ_INDEX         120

#define GM_BANK_MSB       0
#define MODULATION        1
#define DATA_MSB          6
#define PART_VOLUME       7
#define PANPOT            10
#define EXPRESSION        11
#define GM_BANK_LSB       32
#define DATA_LSB          38
#define SUSTAIN           64
#define REVERB            91
#define CHORUS            93
#define RPN_LSB           100
#define RPN_MSB           101
#define RESET_ALL_CTRLS   121
#define ALL_NOTES_OFF     123

#define EV_NOTE_OFF       0x80
#define EV_NOTE_ON        0x90
#define EV_POLY_PRESS     0xa0
#define EV_CONTROL        0xb0
#define EV_PROGRAM        0xc0
#define EV_CHAN_PRESS     0xd0
#define EV_PITCH          0xe0
#define EV_SYSEX          0xf0
#define EV_ESC            0xf7
#define EV_META           0xff

#define META_EOT          0x2f
#define META_TEMPO        0x51
#define META_TIME_SIG     0x58

//
// SAMPLE.system_data[] usage
//

#define SSD_EOD_CALLBACK  0  // Application end-of-data callback if not NULL
#define VOC_BLK_PTR       1  // Pointer to current block
#define VOC_REP_BLK       2  // Pointer to beginning of repeat loop block
#define VOC_N_REPS        3  // # of iterations left in repeat loop
#define VOC_MARKER        4  // Marker to search for, or -1 if all
#define VOC_MARKER_FOUND  5  // Desired marker found if 1, else 0
#define SSD_RELEASE       6  // Release sample handle upon termination if >0
#ifdef IS_WINDOWS
#define SSD_EOD_CB_WIN32S 7  // Application end-of-data callback is in Win32s
#else
#define SSD_TEMP          7  // Temporary storage location for general use
#endif

//
// Timer status values
//

#define AILT_FREE         0         // Timer handle is free for allocation
#define AILT_STOPPED      1         // Timer is stopped
#define AILT_RUNNING      2         // Timer is running

//
// SAMPLE.status flag values
//

#define SMP_FREE          0x0001    // Sample is available for allocation

#define SMP_DONE          0x0002    // Sample has finished playing, or has
                                    // never been started

#define SMP_PLAYING       0x0004    // Sample is playing

#define SMP_STOPPED       0x0008    // Sample has been stopped

#define SMP_PLAYINGBUTRELEASED 0x0010 // Sample is playing, but digital handle
                                      // has been temporarily released



//
// SEQUENCE.status flag values
//

#define SEQ_FREE          0x0001    // Sequence is available for allocation

#define SEQ_DONE          0x0002    // Sequence has finished playing, or has
                                    // never been started

#define SEQ_PLAYING       0x0004    // Sequence is playing

#define SEQ_STOPPED       0x0008    // Sequence has been stopped

#define SEQ_PLAYINGBUTRELEASED 0x0010 // Sequence is playing, but MIDI handle
                                      // has been temporarily released

#ifdef IS_DOS

//
// MIDI driver types
//

#define MDIDRVRTYPE_GM    0         // General MIDI driver (Roland-compatible)
#define MDIDRVRTYPE_FM_2  1         // 2-operator FM MIDI driver (OPL2)
#define MDIDRVRTYPE_FM_4  2         // 4-operator FM MIDI driver (OPL3)
#define MDIDRVRTYPE_SPKR  3         // Tandy or PC speaker "beep" driver

//
// .INI installation result codes
//

#define AIL_INIT_SUCCESS  0         // Driver installed successfully
#define AIL_NO_INI_FILE   1         // No MDI.INI or DIG.INI file exists
#define AIL_INIT_FAILURE  2         // Driver could not be initialized

#ifdef __BORLANDC__

 #ifndef REALPTR
 #define REALPTR(x) ((void *) (U32) ((((U32) (x))>>16<<4) + ((x) & 0xffff) \
                    - AIL_sel_base(_DS)))
 #endif

#else

 #ifndef REALPTR
 #define REALPTR(x) ((void *) (U32) ((((U32) (x))>>16<<4) + ((x) & 0xffff)))
 #endif

#endif

#else

#ifdef IS_WINDOWS

//
// AIL_set_direct_buffer_control() command values
//

#define AILDS_RELINQUISH  0         // App returns control of secondary buffer
#define AILDS_SEIZE       1         // App takes control of secondary buffer
#define AILDS_SEIZE_LOOP  2         // App wishes to loop the secondary buffer

#endif

#endif

//
// General type definitions for portability
//

#ifndef C8
#define C8 char
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef S8
#define S8 signed char
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef S16
#define S16 signed short
#endif

#ifndef U32
#define U32 unsigned long
#endif

#ifndef S32
#define S32 signed long
#endif

#ifndef F32
#define F32 float
#endif

#ifndef F64
#define F64 double
#endif


#ifndef REALFAR
#define REALFAR unsigned long
#endif

#ifndef FILE_ERRS
#define FILE_ERRS

#define AIL_NO_ERROR        0
#define AIL_IO_ERROR        1
#define AIL_OUT_OF_MEMORY   2
#define AIL_FILE_NOT_FOUND  3
#define AIL_CANT_WRITE_FILE 4
#define AIL_CANT_READ_FILE  5
#define AIL_DISK_FULL       6

#endif

#define MIN_VAL 0
#define NOM_VAL 1
#define MAX_VAL 2

#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO  0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE  0
#endif

//
// Preference names and default values
//

#define DIG_RESAMPLING_TOLERANCE   0
#define DEFAULT_DRT                131    // Resampling triggered at +/- 0.2%

#define DIG_MIXER_CHANNELS         1
#define DEFAULT_DMC                64     // 64 allocatable SAMPLE structures

#define DIG_DEFAULT_VOLUME         2
#define DEFAULT_DDV                127    // Default sample volume = 127 (0-127)

#define MDI_SERVICE_RATE           3
#define DEFAULT_MSR                120    // XMIDI sequencer timing = 120 Hz

#define MDI_SEQUENCES              4
#define DEFAULT_MS                 8      // 8 sequence handles/driver

#define MDI_DEFAULT_VOLUME         5
#define DEFAULT_MDV                127    // Default sequence volume = 127 (0-127)

#define MDI_QUANT_ADVANCE          6
#define DEFAULT_MQA                1      // Beat/bar count +1 interval

#define MDI_ALLOW_LOOP_BRANCHING   7
#define DEFAULT_ALB                NO     // Branches cancel XMIDI FOR loops

#define MDI_DEFAULT_BEND_RANGE     8
#define DEFAULT_MDBR               2      // Default pitch-bend range = 2

#ifdef IS_X86

#define MDI_DOUBLE_NOTE_OFF        9
#define DEFAULT_MDNO               NO     // For stuck notes on SB daughterboards

#endif

#define DIG_ENABLE_RESAMPLE_FILTER 31     // Enable resampling filter by
#define DEFAULT_DERF               YES    // default

#define DIG_DECODE_BUFFER_SIZE     32     // 2K decode buffer size by default
#define DEFAULT_DDBS               2048

#if defined(IS_WINDOWS) || defined(IS_MAC)

#define MDI_SYSEX_BUFFER_SIZE      10
#define DEFAULT_MSBS               1536   // Default sysex buffer = 1536 bytes

#define DIG_OUTPUT_BUFFER_SIZE     11
#define DEFAULT_DOBS               49152  // 48K output buffer size

#define AIL_MM_PERIOD              12
#define DEFAULT_AMP                5      // Default MM timer period = 5 msec.

#endif

#ifdef IS_WINDOWS

#define DIG_DS_FRAGMENT_SIZE       34
#define DEFAULT_DDFS               8      // Use 8 millisecond buffer fragments with DirectSound if MSS mixer in use

#define DIG_DS_FRAGMENT_CNT        35
#define DEFAULT_DDFC               96     // Use 96 buffer fragments with DirectSound if MSS mixer in use

#define DIG_DS_MIX_FRAGMENT_CNT    42
#define DEFAULT_DDMFC              8      // Mix ahead 8 buffer fragments

#define DIG_DS_USE_PRIMARY         36
#define DEFAULT_DDUP               NO     // Mix into secondary DirectSound buffer by default

#define DIG_DS_DSBCAPS_CTRL3D      37
#define DEFAULT_DDDC               NO     // Do not use DSBCAPS_CTRL3D by default

#define DIG_DS_CREATION_HANDLER    38
#define DEFAULT_DDCH               NULL   // Use DirectSoundCreate() by default

#define AIL_TIMERS                 13
#define DEFAULT_AT                 16     // 16 allocatable HTIMER handles

#define DIG_MAX_CHAIN_ELEMENT_SIZE 14
#define DEFAULT_MCES               8192   // max of 8192 bytes/waveOut buffer

#define DIG_MIN_CHAIN_ELEMENT_TIME 45
#define DEFAULT_MCET               100    // 100 milliseconds buffers

#define DIG_USE_WAVEOUT            15
#define DEFAULT_DUW                NO     // Use DirectSound by default

#define DIG_DS_SECONDARY_SIZE      16
#define DEFAULT_DDSS               (32*1024L)  // Must be 2^n -- use 32K by default

#define DIG_DS_SAMPLE_CEILING      17
#define DEFAULT_DDSC               44100  // Allow up to 44 kHz samples

#define AIL_LOCK_PROTECTION        18
#define DEFAULT_ALP                NO     // Don't suspend foreground thread by default

#define AIL_WIN32S_CALLBACK_SIZE   19
#define DEFAULT_WCS                4096   // Size of callback data in bytes

#define AIL_MUTEX_PROTECTION       44
#define DEFAULT_AMPR               YES    // Lock each call into Miles with a mutex

#else

#ifdef IS_DOS

#define DIG_SERVICE_RATE          10
#define DEFAULT_DSR               200     // DMA buffer-polling rate = 200 Hz

#define DIG_HARDWARE_SAMPLE_RATE  11
#define DEFAULT_DHSR              NOM_VAL // Use nominal sample rate by default

#define DIG_DMA_RESERVE           12
#define DEFAULT_DDR               32768   // Reserve 32K real-mode mem for DMA

#define DIG_LATENCY               13
#define DEFAULT_DL                100     // Half-buffer size in ms = 100

#define DIG_USE_STEREO            14
#define DEFAULT_DUS               NO      // Use mono output only

#define DIG_USE_16_BITS           15
#define DEFAULT_DU16              NO      // Use 8-bit output by default

#define DIG_ALLOW_16_BIT_DMA      16
#define DEFAULT_DA16DMA           YES     // OK to use 16-bit DMA if necessary

#define DIG_SS_LOCK               17
#define DEFAULT_DSL               NO      // Don't disable IRQs while mixing

#define AIL_SCAN_FOR_HARDWARE     18
#define DEFAULT_ASH               YES     // Scan for I/O settings if necessary

#define AIL_ALLOW_VDM_EXECUTION   19
#define DEFAULT_AVE               YES     // Allow Windows "DOS box" execution

#endif

#endif

// ----------------------------------
// DLS Preference names and default values
// Unless otherwise specified, values must be established
// BEFORE calling DLSMSSOpen()!
// ----------------------------------

#define DLS_TIMEBASE               20
#define DEFAULT_DTB                120  // 120 intervals/second by default

#define DLS_VOICE_LIMIT            21
#define DEFAULT_DVL                24   // 24 voices supported

#define DLS_BANK_SELECT_ALIAS      22
#define DEFAULT_DBSA               NO   // Do not treat controller 114 as bank

#define DLS_STREAM_BOOTSTRAP       23   // Don't submit first stream buffer
#define DEFAULT_DSB                YES  // until at least 2 available

#define DLS_VOLUME_BOOST           24
#define DEFAULT_DVB                0    // Boost final volume by 0 dB

#define DLS_ENABLE_FILTERING       25   // Filtering = on by default
#define DEFAULT_DEF                YES  // (may be changed at any time)

#ifdef IS_X86

#define AIL_ENABLE_MMX_SUPPORT     27   // Enable MMX support if present
#define DEFAULT_AEMS               YES  // (may be changed at any time)

#endif

#define DLS_GM_PASSTHROUGH         28   // Pass unrecognized traffic on to
#define DEFAULT_DGP                YES  // default GM driver layer
                                        // (may be changed at any time)

#define DLS_ADPCM_TO_ASI_THRESHOLD 39   // Size in samples to switch to ASI
#define DEFAULT_DATAT              32768

//
// Add'l platform-independent prefs
//

#define DIG_REVERB_BUFFER_SIZE     40
#define DEFAULT_DRBS               0    // No reverb support by default

#define DIG_INPUT_LATENCY          41   // Use >= 250-millisecond input buffers if
#define DEFAULT_DIL                250  // explicit size request cannot be satisfied

#ifdef IS_WINDOWS

#define DIG_USE_WAVEIN             43
#define DEFAULT_DUWI               YES  // Use waveIn for input by default

#endif

#define N_PREFS 46                      // # of preference types

typedef struct _AILSOUNDINFO {
  S32 format;
  void const FAR* data_ptr;
  U32 data_len;
  U32 rate;
  S32 bits;
  S32 channels;
  U32 samples;
  U32 block_size;
  void const FAR* initial_ptr;
} AILSOUNDINFO;


// for multi-processor machines

#ifdef IS_WIN32

#ifdef BUILD_MSS

  #define MSSLockedIncrement(var) _asm { lock inc [var] }
  #define MSSLockedDecrement(var) _asm { lock dec [var] }

  static void __MSSLockedIncrementAddr(void * addr)
  {
    _asm
    {
      mov eax,[addr]
      lock inc dword ptr [eax]
    }
  }

  static void __MSSLockedDecrementAddr(void * addr)
  {
    _asm {
      mov eax,[addr]
      lock dec dword ptr [eax]
    }
  }

  #define MSSLockedIncrementPtr(var) __MSSLockedIncrementAddr(&(var))
  #define MSSLockedDecrementPtr(var) __MSSLockedDecrementAddr(&(var))

#else

  #define MSSLockedIncrement(var) (++var)
  #define MSSLockedDecrement(var) (--var)

  #define MSSLockedIncrementPtr(var) (++var)
  #define MSSLockedDecrementPtr(var) (--var)

#endif

#else
  #define MSSLockedIncrement(var) (++var)
  #define MSSLockedDecrement(var) (--var)

  #define MSSLockedIncrementPtr(var) (++var)
  #define MSSLockedDecrementPtr(var) (--var)
#endif

#ifndef RIB_H        // RIB.H contents included if RIB.H not already included

// #include "rib.h"

#define RIB_H
#define ARY_CNT(x) (sizeof((x)) / sizeof((x)[0]))

// ----------------------------------
// RIB data types
// ----------------------------------

typedef S32 RIBRESULT;

#define RIB_NOERR                    0   // Success -- no error
#define RIB_NOT_ALL_AVAILABLE        1   // Some requested functions/attribs not available
#define RIB_NOT_FOUND                2   // Resource not found
#define RIB_OUT_OF_MEM               3   // Out of system RAM

//
// Handle to interface provider
//

typedef U32 HPROVIDER;

//
// Handle representing token used to obtain attribute or preference
// data from RIB provider
//

typedef U32 HATTRIB;

//
// Handle representing an enumerated interface entry
//
// RIB_enumerate_interface() returns 1 if valid next entry found, else
// 0 if end of list reached
//

typedef U32 HINTENUM;
#define HINTENUM_FIRST 0

//
// Handle representing an enumerated provider entry
//
// RIB_enumerate_providers() returns 1 if valid next entry found, else
// 0 if end of list reached
//

typedef U32 HPROENUM;
#define HPROENUM_FIRST 0

//
// Data types for RIB attributes and preferences
//

typedef enum
{
   RIB_NONE = 0, // No type
   RIB_CUSTOM,   // Used for pointers to application-specific structures
   RIB_DEC,      // Used for 32-bit integer values to be reported in decimal
   RIB_HEX,      // Used for 32-bit integer values to be reported in hex
   RIB_FLOAT,    // Used for 32-bit single-precision FP values
   RIB_PERCENT,  // Used for 32-bit single-precision FP values to be reported as percentages
   RIB_BOOL,     // Used for Boolean-constrained integer values to be reported as TRUE or FALSE
   RIB_STRING    // Used for pointers to null-terminated ASCII strings
}
RIB_DATA_SUBTYPE;

//
// RIB_ENTRY_TYPE structure, used to register an interface or request one
//

typedef enum
{
   RIB_FUNCTION = 0,
   RIB_ATTRIBUTE,     // Attribute: read-only data type used for status/info communication
   RIB_PREFERENCE     // Preference: read/write data type used to control behavior
}
RIB_ENTRY_TYPE;

//
// RIB_INTERFACE_ENTRY, used to represent a function or data entry in an
// interface
//

typedef struct
{
   RIB_ENTRY_TYPE   type;        // See list above
   C8 FAR          *entry_name;  // Name of desired function or attribute
   U32              token;       // Function pointer or attribute token
   RIB_DATA_SUBTYPE subtype;     // Data (attrib or preference) subtype
}
RIB_INTERFACE_ENTRY;

//
// Standard RAD Interface Broker provider identification attributes
//

#define PROVIDER_NAME    (-100)  // RIB_STRING name of decoder
#define PROVIDER_VERSION (-101)  // RIB_HEX BCD version number

//
// Standard function to obtain provider attributes (see PROVIDER_ defines
// above)
//
// Each provider of a searchable interface must export this function
//

typedef U32 (AILCALL FAR *PROVIDER_QUERY_ATTRIBUTE) (HATTRIB index);

//
// Macros to simplify interface registrations/requests for functions,
// attributes, and preferences
//

#define FN(entry_name)        { RIB_FUNCTION, #entry_name, (U32) &(entry_name), RIB_NONE }
#define REG_FN(entry_name)    { RIB_FUNCTION, #entry_name, (U32) &(entry_name), RIB_NONE }

#define AT(entry_name,ID)             { RIB_ATTRIBUTE, (entry_name), (U32) &(ID), RIB_NONE }
#define REG_AT(entry_name,ID,subtype) { RIB_ATTRIBUTE, (entry_name), (U32)  (ID), subtype  }

#define PR(entry_name,ID)             { RIB_PREFERENCE, (entry_name), (U32) &(ID), RIB_NONE }
#define REG_PR(entry_name,ID,subtype) { RIB_PREFERENCE, (entry_name), (U32)  (ID), subtype  }

#define RIB_register(x,y,z)   RIB_register_interface  (HPROVIDER(x), y, ARY_CNT(z), z)
#define RIB_unregister(x,y,z) RIB_unregister_interface(HPROVIDER(x), y, ARY_CNT(z), z)
#define RIB_unregister_all(x) RIB_unregister_interface(HPROVIDER(x), NULL, 0, NULL)
#define RIB_free_libraries()  RIB_free_provider_library(HPROVIDER(NULL));
#define RIB_request(x,y,z)    RIB_request_interface   (x, y, ARY_CNT(z), z)

// ----------------------------------
// Standard RIB API prototypes
// ----------------------------------

DXDEC  HPROVIDER  AILCALL RIB_alloc_provider_handle   (U32            module);
DXDEC  void       AILCALL RIB_free_provider_handle    (HPROVIDER      provider);

DXDEC  HPROVIDER  AILCALL RIB_load_provider_library   (C8 const FAR *filename);
DXDEC  void       AILCALL RIB_free_provider_library   (HPROVIDER      provider);

DXDEC  HPROVIDER  AILCALL RIB_provider_library_handle (void);

DXDEC  RIBRESULT  AILCALL RIB_register_interface      (HPROVIDER                      provider,
                                                       C8 const FAR                   *interface_name,
                                                       S32                            entry_count,
                                                       RIB_INTERFACE_ENTRY const FAR *rlist);

DXDEC  RIBRESULT  AILCALL RIB_unregister_interface    (HPROVIDER                      provider,
                                                       C8 const FAR                  *interface_name,
                                                       S32                            entry_count,
                                                       RIB_INTERFACE_ENTRY const FAR *rlist);

DXDEC  RIBRESULT  AILCALL RIB_request_interface       (HPROVIDER                provider,
                                                       C8 const FAR            *interface_name,
                                                       S32                      entry_count,
                                                       RIB_INTERFACE_ENTRY FAR *rlist);

DXDEC  RIBRESULT  AILCALL RIB_request_interface_entry (HPROVIDER                provider,
                                                       C8 const FAR            *interface_name,
                                                       RIB_ENTRY_TYPE           entry_type,
                                                       C8 const FAR            *entry_name,
                                                       U32 FAR                 *token);

DXDEC  S32        AILCALL RIB_enumerate_interface     (HPROVIDER                provider,
                                                       C8 FAR             *interface_name,
                                                       RIB_ENTRY_TYPE           type,
                                                       HINTENUM FAR            *next,
                                                       RIB_INTERFACE_ENTRY FAR *dest);

DXDEC  S32        AILCALL RIB_enumerate_providers     (C8 FAR                  *interface_name,
                                                       HPROENUM FAR            *next,
                                                       HPROVIDER FAR           *dest);

DXDEC  C8 FAR *   AILCALL RIB_type_string             (U32                      data,
                                                       RIB_DATA_SUBTYPE         subtype);

DXDEC  HPROVIDER  AILCALL RIB_find_file_provider      (C8 const FAR            *interface_name,
                                                       C8 const FAR            *attribute_name,
                                                       C8 const FAR            *file_suffix);

DXDEC  HPROVIDER  AILCALL RIB_find_provider           (C8 const FAR            *interface_name,
                                                       C8 const FAR            *attribute_name,
                                                       C8 const FAR            *attribute_value);

DXDEC  HPROVIDER  AILCALL RIB_find_files_provider     (C8 const FAR *interface_name,
                                                       C8 const FAR *attribute_name_1,
                                                       C8 const FAR *file_suffix_1,
                                                       C8 const FAR *attribute_name_2,
                                                       C8 const FAR *file_suffix_2);

DXDEC  HPROVIDER  AILCALL RIB_find_file_dec_provider  (C8 const FAR *interface_name,
                                                       C8 const FAR *attribute_name_1,
                                                       U32 attribute_value_1,
                                                       C8 const FAR *attribute_name_2,
                                                       C8 const FAR *file_suffix_2);

DXDEC  S32        AILCALL RIB_load_application_providers
                                                      (C8 const FAR  *filespec);

DXDEC  void       AILCALL RIB_set_provider_user_data  (HPROVIDER provider,
                                                       U32       index,
                                                       S32       value);

DXDEC  S32        AILCALL RIB_provider_user_data      (HPROVIDER provider,
                                                       U32       index);

DXDEC  void       AILCALL RIB_set_provider_system_data
                                                      (HPROVIDER provider,
                                                       U32       index,
                                                       S32       value);

DXDEC  S32        AILCALL RIB_provider_system_data    (HPROVIDER provider,
                                                       U32       index);

DXDEC  C8 FAR *  AILCALL  RIB_error                   (void);

#endif

#ifndef MSS_ASI_VERSION // MSSASI.H contents included if MSSASI.H not already included

// #include "mssasi.h"

#define AIL_ASI_VERSION  1
#define AIL_ASI_REVISION 0

//
// Handle to stream being managed by ASI codec
//

typedef S32 HASISTREAM;

//
// ASI result codes
//

typedef S32 ASIRESULT;

#define ASI_NOERR                   0   // Success -- no error
#define ASI_NOT_ENABLED             1   // ASI not enabled
#define ASI_ALREADY_STARTED         2   // ASI already started
#define ASI_INVALID_PARAM           3   // Invalid parameters used
#define ASI_INTERNAL_ERR            4   // Internal error in ASI driver
#define ASI_OUT_OF_MEM              5   // Out of system RAM
#define ASI_ERR_NOT_IMPLEMENTED     6   // Feature not implemented
#define ASI_NOT_FOUND               7   // ASI supported device not found
#define ASI_NOT_INIT                8   // ASI not initialized
#define ASI_CLOSE_ERR               9   // ASI not closed correctly

// ----------------------------------
// Application-provided ASI callbacks
// ----------------------------------

//
// AILASIFETCHCB: Called by ASI to obtain data from stream source
//
// offset normally will be either 0 at the first call made by the codec
// or -1 to specify a continuous stream, except when ASI_stream_seek()
// is called to restart the stream codec at a new stream offset.  In this
// case, the application must execute the seek operation on the ASI codec's
// behalf.
//
// In response to this callback, the application should read the requested
// data and copy it to the specified destination buffer, returning the number
// of bytes copied (which can be less than bytes_requested if the end of
// the stream is reached).
//

typedef S32 (AILCALLBACK FAR * AILASIFETCHCB) (U32       user,            // User value passed to ASI_open_stream()
                                               void FAR *dest,            // Location to which stream data should be copied by app
                                               S32       bytes_requested, // # of bytes requested by ASI codec
                                               S32       offset);         // If not -1, application should seek to this point in stream

//############################################################################
//##                                                                        ##
//## Interface "ASI codec"                                                  ##
//##                                                                        ##
//############################################################################

//
// Initialize ASI stream codec
//
// No other ASI functions may be called outside an ASI_startup() /
// ASI_shutdown() pair, except for the standard RIB function
// PROVIDER_query_attribute().  All provider attributes must be accessible
// without starting up the codec.
//

typedef ASIRESULT (AILCALL FAR *ASI_STARTUP)(void);

//
// Shut down ASI codec
//

typedef ASIRESULT (AILCALL FAR * ASI_SHUTDOWN)(void);

//
// Return codec error message, or NULL if no errors have occurred since
// last call
//
// The ASI error text state is global to all streams
//

typedef C8 FAR *  (AILCALL FAR * ASI_ERROR)(void);

//############################################################################
//##                                                                        ##
//## Interface "ASI stream"                                                 ##
//##                                                                        ##
//############################################################################

//
// Open a stream, returning handle to stream
//

typedef HASISTREAM (AILCALL FAR *ASI_STREAM_OPEN) (U32           user,              // User value passed to fetch callback
                                                   AILASIFETCHCB fetch_CB,          // Source data fetch handler
                                                   U32           total_size);       // Total size for %-done calculations (0=unknown)

//
// Translate data in stream, returning # of bytes actually decoded or encoded
//
// Any number of bytes may be requested.  Requesting more data than is
// available in the codec's internal buffer will cause the AILASIFETCHCB
// handler to be called to fetch more data from the stream.
//

typedef S32  (AILCALL FAR *ASI_STREAM_PROCESS) (HASISTREAM  stream,              // Handle of stream
                                                void FAR   *buffer,              // Destination for processed data
                                                S32         buffer_size);        // # of bytes to return in buffer

//
// Restart stream decoding process at new offset
//
// Relevant for decoders only
//
// Seek destination is given as offset in bytes from beginning of stream
//
// At next ASI_stream_process() call, decoder will seek to the closest possible
// point in the stream which occurs at or after the specified position
//
// This function has no effect for decoders which do not support random 
// seeks on a given stream type
//
// Warning: some decoders may need to implement seeking by reparsing
// the entire stream up to the specified offset, through multiple calls
// to the data-fetch callback.  This operation may be extremely
// time-consuming on large files or slow network connections.
//
// A stream_offset value of -1 may be used to inform the decoder that the
// application has changed the input stream offset on its own, e.g. for a
// double-buffering application where the ASI decoder is not accessing the
// stream directly.  ASI decoders should respond to this by flushing all
// internal buffers and resynchronizing themselves to the data stream.
//

typedef ASIRESULT (AILCALL FAR *ASI_STREAM_SEEK)    (HASISTREAM stream,
                                                     S32        stream_offset);

//
// Retrieve an ASI stream attribute or preference value by index
//

typedef S32 (AILCALL FAR *ASI_STREAM_ATTRIBUTE) (HASISTREAM stream,
                                                 HATTRIB    attrib);

//
// Set an ASI stream preference value by index
//

typedef S32 (AILCALL FAR *ASI_STREAM_SET_PREFERENCE) (HASISTREAM stream,
                                                      HATTRIB    preference,
                                                      void const FAR  *  value);

//
// Close stream, freeing handle and all internally-allocated resources
//

typedef ASIRESULT (AILCALL FAR *ASI_STREAM_CLOSE) (HASISTREAM stream);

#endif

//############################################################################
//##                                                                        ##
//## Interface "MSS 3D audio services"                                      ##
//##                                                                        ##
//############################################################################

//
// 3D positioning services
//


typedef struct h3DPOBJECT
{
  U32 junk;
} h3DPOBJECT;

typedef h3DPOBJECT FAR * H3DPOBJECT;
typedef H3DPOBJECT H3DSAMPLE;

//
// M3D result codes
//

typedef S32 M3DRESULT;

#define M3D_NOERR                   0   // Success -- no error
#define M3D_NOT_ENABLED             1   // M3D not enabled
#define M3D_ALREADY_STARTED         2   // M3D already started
#define M3D_INVALID_PARAM           3   // Invalid parameters used
#define M3D_INTERNAL_ERR            4   // Internal error in M3D driver
#define M3D_OUT_OF_MEM              5   // Out of system RAM
#define M3D_ERR_NOT_IMPLEMENTED     6   // Feature not implemented
#define M3D_NOT_FOUND               7   // M3D supported device not found
#define M3D_NOT_INIT                8   // M3D not initialized
#define M3D_CLOSE_ERR               9   // M3D not closed correctly


typedef void (AILCALLBACK FAR* AIL3DSAMPLECB)   (H3DSAMPLE sample);

typedef M3DRESULT (AILCALL FAR *M3D_STARTUP)(void);

typedef M3DRESULT (AILCALL FAR *M3D_SHUTDOWN)(void);

typedef C8 FAR *  (AILCALL FAR *M3D_ERROR)(void);

typedef S32       (AILCALL FAR *M3D_SET_PROVIDER_PREFERENCE)(HATTRIB preference,
                                                             void const FAR *  value);

typedef M3DRESULT  (AILCALL FAR * M3D_ACTIVATE)(S32 enable);

typedef H3DSAMPLE  (AILCALL FAR * M3D_ALLOCATE_3D_SAMPLE_HANDLE)(void);


typedef void       (AILCALL FAR * M3D_RELEASE_3D_SAMPLE_HANDLE)(H3DSAMPLE samp);
                                       

typedef void       (AILCALL FAR * M3D_START_3D_SAMPLE)(H3DSAMPLE samp);


typedef void       (AILCALL FAR * M3D_STOP_3D_SAMPLE)(H3DSAMPLE samp);
                                       

typedef void       (AILCALL FAR * M3D_RESUME_3D_SAMPLE)(H3DSAMPLE samp);
                                      
typedef void       (AILCALL FAR * M3D_END_3D_SAMPLE)(H3DSAMPLE samp);

typedef S32        (AILCALL FAR * M3D_SET_3D_SAMPLE_DATA)(H3DSAMPLE         samp,
                                                          AILSOUNDINFO const FAR  *info);

typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_VOLUME)(H3DSAMPLE samp,
                                                            S32       volume);

typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_PLAYBACK_RATE)(H3DSAMPLE samp,
                                                                   S32       playback_rate);

typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_OFFSET)(H3DSAMPLE samp,
                                                            U32       offset);


typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_LOOP_COUNT)(H3DSAMPLE samp,
                                                                U32       loops);

typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_LOOP_BLOCK)(H3DSAMPLE S,
                                                                S32       loop_start_offset,
                                                                S32       loop_end_offset);

typedef U32        (AILCALL FAR * M3D_3D_SAMPLE_STATUS)(H3DSAMPLE samp);

typedef U32        (AILCALL FAR * M3D_3D_SAMPLE_ATTRIBUTE)(H3DSAMPLE samp, HATTRIB index);

typedef S32        (AILCALL FAR * M3D_3D_SET_SAMPLE_PREFERENCE)(H3DSAMPLE samp, HATTRIB preference, void const FAR * value);

typedef S32        (AILCALL FAR * M3D_3D_SAMPLE_VOLUME)(H3DSAMPLE samp);

typedef S32        (AILCALL FAR * M3D_3D_SAMPLE_PLAYBACK_RATE)(H3DSAMPLE samp);

typedef U32        (AILCALL FAR * M3D_3D_SAMPLE_OFFSET)(H3DSAMPLE     samp);

typedef U32        (AILCALL FAR * M3D_3D_SAMPLE_LENGTH)(H3DSAMPLE     samp);

typedef U32        (AILCALL FAR * M3D_3D_SAMPLE_LOOP_COUNT)(H3DSAMPLE samp);

typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_DISTANCES)(H3DSAMPLE samp,
                                                               F32       max_dist,
                                                               F32       min_dist);


typedef void       (AILCALL FAR * M3D_3D_SAMPLE_DISTANCES)(H3DSAMPLE samp,
                                                           F32 FAR * max_dist,
                                                           F32 FAR * min_dist);

typedef  S32      (AILCALL FAR * M3D_ACTIVE_3D_SAMPLE_COUNT)(void);

typedef H3DPOBJECT (AILCALL FAR * M3D_3D_OPEN_LISTENER)(void);

typedef void       (AILCALL FAR * M3D_3D_CLOSE_LISTENER)(H3DPOBJECT listener);

typedef H3DPOBJECT (AILCALL FAR * M3D_3D_OPEN_OBJECT)(void);

typedef void       (AILCALL FAR * M3D_3D_CLOSE_OBJECT)(H3DPOBJECT obj);

typedef void       (AILCALL FAR * M3D_SET_3D_POSITION)(H3DPOBJECT obj,
                                                       F32     X,
                                                       F32     Y,
                                                       F32     Z);

typedef void       (AILCALL FAR * M3D_SET_3D_VELOCITY)(H3DPOBJECT obj,
                                                       F32     dX_per_ms,
                                                       F32     dY_per_ms,
                                                       F32     dZ_per_ms,
                                                       F32     magnitude);

typedef void       (AILCALL FAR * M3D_SET_3D_VELOCITY_VECTOR)(H3DPOBJECT obj,
                                                              F32     dX_per_ms,
                                                              F32     dY_per_ms,
                                                              F32     dZ_per_ms);

typedef void       (AILCALL FAR * M3D_SET_3D_ORIENTATION)(H3DPOBJECT obj,
                                                          F32     X_face,
                                                          F32     Y_face,
                                                          F32     Z_face,
                                                          F32     X_up,
                                                          F32     Y_up,
                                                          F32     Z_up);

typedef void       (AILCALL FAR * M3D_3D_POSITION)(H3DPOBJECT  obj,
                                                   F32 FAR *X,
                                                   F32 FAR *Y,
                                                   F32 FAR *Z);

typedef void       (AILCALL FAR * M3D_3D_VELOCITY)(H3DPOBJECT  obj,
                                                   F32 FAR *dX_per_ms,
                                                   F32 FAR *dY_per_ms,
                                                   F32 FAR *dZ_per_ms);

typedef void       (AILCALL FAR * M3D_3D_ORIENTATION)(H3DPOBJECT  obj,
                                                      F32 FAR *X_face,
                                                      F32 FAR *Y_face,
                                                      F32 FAR *Z_face,
                                                      F32 FAR *X_up,
                                                      F32 FAR *Y_up,
                                                      F32 FAR *Z_up);

typedef void       (AILCALL FAR * M3D_3D_UPDATE_POSITION)(H3DPOBJECT obj,
                                                          F32     dt_milliseconds);

typedef void       (AILCALL FAR * M3D_3D_AUTO_UPDATE_POSITION)(H3DPOBJECT obj,
                                                               S32        enable);

typedef S32        (AILCALL FAR * M3D_3D_ROOM_TYPE)(void);
typedef void       (AILCALL FAR * M3D_SET_3D_ROOM_TYPE)(S32 EAX_room_type);
typedef S32        (AILCALL FAR * M3D_3D_SPEAKER_TYPE)(void);
typedef void       (AILCALL FAR * M3D_SET_3D_SPEAKER_TYPE)(S32 speaker_type);
typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_OBSTRUCTION)(H3DSAMPLE samp, F32 obstruction);
typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_OCCLUSION)(H3DSAMPLE samp, F32 occlusion);
typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_EFFECTS_LEVEL)(H3DSAMPLE samp, F32 effects_level);
typedef F32        (AILCALL FAR * M3D_3D_SAMPLE_OBSTRUCTION)(H3DSAMPLE samp);
typedef F32        (AILCALL FAR * M3D_3D_SAMPLE_OCCLUSION)(H3DSAMPLE samp);
typedef F32        (AILCALL FAR * M3D_3D_SAMPLE_EFFECTS_LEVEL)(H3DSAMPLE samp);

typedef AIL3DSAMPLECB (AILCALL FAR * M3D_SET_3D_EOS)(H3DSAMPLE client,H3DSAMPLE samp,AIL3DSAMPLECB cb);

typedef void       (AILCALL FAR * M3D_SET_3D_SAMPLE_CONE)(H3DSAMPLE samp, F32 inner_angle, F32 outer_angle, S32 outer_volume);
typedef void       (AILCALL FAR * M3D_3D_SAMPLE_CONE)(H3DSAMPLE samp, F32 FAR* inner_angle, F32 FAR* outer_angle, S32 FAR* outer_volume);

//############################################################################
//##                                                                        ##
//## Interface "MSS mixer services"                                         ##
//##                                                                        ##
//############################################################################

//
// Operation flags used by mixer module
//

#define M_DEST_STEREO 1       // Set to enable stereo mixer output
#define M_SRC_16      2       // Set to enable mixing of 16-bit samples
#define M_FILTER      4       // Set to enable filtering when resampling
#define M_SRC_STEREO  8       // Set to enable mixing of stereo input samples
#define M_VOL_SCALING 16      // Set to enable volume scalars other than 2047
#define M_RESAMPLE    32      // Set to enable playback ratios other than 65536
#define M_ORDER       64      // Set to reverse L/R stereo order for sample

#ifdef IS_32

//
// Initialize mixer
//
// No other mixer functions may be called outside a MIXER_startup() /
// MIXER_shutdown() pair, except for the standard RIB function
// PROVIDER_query_attribute().  All provider attributes must be accessible
// without starting up the module.
//

typedef void (AILCALL FAR *MIXER_STARTUP)(void);

//
// Shut down mixer
//

typedef void (AILCALL FAR *MIXER_SHUTDOWN)(void);

//
// Flush mixer buffer
//

typedef void (AILCALL FAR *MIXER_FLUSH)   (S32 FAR *dest,
                                           S32      len,
                                           S32 FAR *reverb_buffer,
                                           S32      reverb_level
#ifdef IS_X86
                                           ,U32             MMX_available
#endif
                                           );

//
// Perform audio mixing operation
//

typedef void (AILCALL FAR *MIXER_MERGE)   (void const FAR * FAR *src,
                                           U32        FAR *src_fract,
                                           void const FAR *src_end,
                                           S32  FAR * FAR *dest,
                                           void FAR       *dest_end,
                                           S32  FAR       *left_val,
                                           S32  FAR       *right_val,
                                           S32             playback_ratio,
                                           S32             scale_left,
                                           S32             scale_right,
                                           U32             operation
#ifdef IS_X86
                                           ,U32             MMX_available
#endif
                                           );

//
// Translate mixer buffer contents to final output format
//

#ifdef IS_MAC

typedef void (AILCALL FAR *MIXER_COPY) (void const FAR  *src,
                                        S32       src_len,
                                        void FAR *dest,
                                        U32       operation,
                                        U32       big_endian_output);
#else

typedef void (AILCALL FAR *MIXER_COPY) (void const FAR  *src,
                                        S32       src_len,
                                        void FAR *dest,
                                        U32       operation,
                                        U32       MMX_available);
#endif
#else

//
// Initialize mixer
//
// No other mixer functions may be called outside a MIXER_startup() /
// MIXER_shutdown() pair, except for the standard RIB function
// PROVIDER_query_attribute().  All provider attributes must be accessible
// without starting up the module.
//

typedef void (AILCALL FAR *MIXER_STARTUP)(void);

//
// Shut down mixer
//

typedef void (AILCALL FAR *MIXER_SHUTDOWN)(void);

//
// Flush mixer buffer
//

typedef void (AILCALL FAR *MIXER_FLUSH)   (S32 FAR *dest,
                                           S32      len,
                                           S32 FAR *reverb_buffer,
                                           S32      reverb_level,
                                           U32      MMX_available);

//
// Perform audio mixing operation
//

typedef void (AILCALL FAR *MIXER_MERGE)   (U32             src_sel,
                                           U32             dest_sel,
                                           U32        FAR *src_fract,
                                           U32        FAR *src_offset,
                                           U32        FAR *dest_offset,
                                           U32             src_end_offset,
                                           U32             dest_end_offset,
                                           S32  FAR       *left_val,
                                           S32  FAR       *right_val,
                                           S32             playback_ratio,
                                           S32             scale_both,
                                           U32             operation);

//
// Translate mixer buffer contents to final output format
//

typedef void (AILCALL FAR *MIXER_COPY) (void const FAR *src,
                                        S32       src_len,
                                        void FAR *dest,
                                        U32       operation,
                                        U32       MMX_available);
#endif

//
// Type definitions
//

struct _DIG_DRIVER;

struct _MDI_DRIVER;

typedef struct _DIG_DRIVER FAR * HDIGDRIVER;    // Handle to digital driver

typedef struct _MDI_DRIVER FAR * HMDIDRIVER;    // Handle to XMIDI driver

typedef struct _SAMPLE FAR * HSAMPLE;           // Handle to sample

typedef struct _SEQUENCE FAR * HSEQUENCE;       // Handle to sequence

typedef S32 HTIMER;                             // Handle to timer


#ifdef IS_DOS

//
// Type definitions
//

typedef struct                      // I/O parameters structure
{
   S16 IO;
   S16 IRQ;
   S16 DMA_8_bit;
   S16 DMA_16_bit;
   S32 IO_reserved[4];
}
IO_PARMS;

typedef struct                      // Standard MSS 3.X VDI driver header
{
   S8     ID[8];                    // "AIL3xxx" ID string, followed by ^Z

   U32    driver_version;

   REALFAR  common_IO_configurations;
   U16    num_IO_configurations;

   REALFAR  environment_string;

   IO_PARMS IO;

   S16     service_rate;

   U16    busy;

   U16    driver_num;             // Driver number

   U16    this_ISR;               // Offset of INT 66H dispatcher
   REALFAR  prev_ISR;               // Pointer to previous INT 66H ISR

   S8     scratch[128];           // Shared scratch workspace

   S8     dev_name[80];           // Device name (VDI version >= 1.12 only)
}
VDI_HDR;

typedef struct
{
   U16 minimum_physical_sample_rate;
   U16 nominal_physical_sample_rate;
   U16 maximum_physical_sample_rate;

   U16 minimum_DMA_half_buffer_size;
   U16 maximum_DMA_half_buffer_size;

   U32 flags;
}
DIG_MODE;

typedef struct
{
   U8    format_supported[16];
   DIG_MODE format_data[16];
}
DIG_DDT;

typedef struct
{
   REALFAR  DMA_buffer_A;
   REALFAR  DMA_buffer_B;
   S16     active_buffer;
}
DIG_DST;

typedef struct
{
   REALFAR  library_environment;
   REALFAR  GTL_suffix;

   U16    num_voices;

   U16    max_melodic_channel;
   U16    min_melodic_channel;
   U16    percussion_channel;
}
MDI_DDT;

typedef struct
{
   S8     library_directory[128];
   S8     GTL_filename[128];

   S8     MIDI_data[512];
}
MDI_DST;

typedef struct                   // Initialization file structure
{
   char     device_name[128];    // Device name
   char     driver_name[128];    // Driver filename
   IO_PARMS IO;                  // I/O parameters for driver
}
AIL_INI;

typedef struct                   // Handle to driver
{
   REALFAR  seg;                 // Seg:off pointer to driver (off=0)
   U32    sel;                   // Selector for driver (off=0)
   void    *buf;                 // Protected-mode pointer to driver
   U32    size;                  // Size of driver image
   VDI_HDR *VHDR;                // Pointer to driver header (same as buf)
   S32     type;                 // AIL3DIG or AIL3MDI (see below)

   S32     initialized;          // 1 if hardware successfully init'd, else 0

   S32     PM_ISR;               // -1 if no PM ISR hooked, else IRQ #

   HTIMER   server;              // DRV_SERVE periodic timer, if requested

                                 // Vector to high-level destructor, if any

   void (AILCALL *destructor)(HDIGDRIVER);

                                 // High-level descriptor (DIG_ or MDI_DRIVER)
   void        *descriptor;
}
AIL_DRIVER;

typedef struct                     // VDI interface register structure
{
   S16 AX;
   S16 BX;
   S16 CX;
   S16 DX;
   S16 SI;
   S16 DI;
}
VDI_CALL;

#endif

//
// Function pointer types
//

typedef void (AILCALLBACK FAR* AILINCB)       (void const FAR *data, S32 len, U32 user_data);

typedef void (AILCALLBACK FAR* AILTIMERCB)    (U32 user);

typedef void (AILCALLBACK FAR* AILSAMPLECB)   (HSAMPLE sample);

typedef S32  (AILCALLBACK FAR* AILEVENTCB)    (HMDIDRIVER hmi,HSEQUENCE seq,S32 status,S32 data_1,S32 data_2);

typedef S32  (AILCALLBACK FAR* AILTIMBRECB)   (HMDIDRIVER hmi,S32 bank,S32 patch);

typedef S32  (AILCALLBACK FAR* AILPREFIXCB)   (HSEQUENCE seq,S32 log,S32 data);

typedef void (AILCALLBACK FAR* AILTRIGGERCB)  (HSEQUENCE seq,S32 log,S32 data);

typedef void (AILCALLBACK FAR* AILBEATCB)     (HMDIDRIVER hmi,HSEQUENCE seq,S32 beat,S32 measure);

typedef void (AILCALLBACK FAR* AILSEQUENCECB) (HSEQUENCE seq);

//
// Handle to sample and driver being managed by pipeline filter
//

typedef S32 HSAMPLESTATE;
typedef S32 HDRIVERSTATE;

//
// Digital pipeline stages
//
// These are the points at which external modules may be installed into
// a given HSAMPLE or HDIGDRIVER's processing pipeline
//

typedef enum
{
   DP_ASI_DECODER=0,   // Must be "ASI codec stream" provider
   DP_FILTER,        // Must be "MSS pipeline filter" provider
   DP_MERGE,         // Must be "MSS mixer" provider
   N_SAMPLE_STAGES,  // Placeholder for end of list (= # of valid stages)
   SAMPLE_ALL_STAGES // Used to signify all pipeline stages, for shutdown
}
SAMPLESTAGE;

typedef enum
{
   DP_FLUSH = 0,     // Must be "MSS mixer" provider
   DP_DEFAULT_FILTER, // Must be "MSS pipeline filter" provider (sets the default)
   DP_DEFAULT_MERGE,  // Must be "MSS mixer" provider (sets the default)
   DP_COPY,          // Must be "MSS mixer" provider
   N_DIGDRV_STAGES,  // Placeholder for end of list (= # of valid stages)
   DIGDRV_ALL_STAGES // Used to signify all pipeline stages, for shutdown
}
DIGDRVSTAGE;

typedef struct
   {
   ASI_STREAM_OPEN           ASI_stream_open;
   ASI_STREAM_PROCESS        ASI_stream_process;
   ASI_STREAM_SEEK           ASI_stream_seek;
   ASI_STREAM_CLOSE          ASI_stream_close;
   ASI_STREAM_ATTRIBUTE      ASI_stream_attribute;
   ASI_STREAM_SET_PREFERENCE ASI_stream_set_preference;

   HATTRIB INPUT_BIT_RATE;
   HATTRIB INPUT_SAMPLE_RATE;
   HATTRIB INPUT_BITS;
   HATTRIB INPUT_CHANNELS;
   HATTRIB OUTPUT_BIT_RATE;
   HATTRIB OUTPUT_SAMPLE_RATE;
   HATTRIB OUTPUT_BITS;
   HATTRIB OUTPUT_CHANNELS;
   HATTRIB POSITION;
   HATTRIB PERCENT_DONE;
   HATTRIB MIN_INPUT_BLOCK_SIZE;
   HATTRIB RAW_RATE;
   HATTRIB RAW_BITS;
   HATTRIB RAW_CHANNELS;
   HATTRIB REQUESTED_RATE;
   HATTRIB REQUESTED_BITS;
   HATTRIB REQUESTED_CHANS;

   HASISTREAM stream;
   }
ASISTAGE;

typedef struct
   {
   MIXER_FLUSH MSS_mixer_flush;
   MIXER_MERGE MSS_mixer_merge;
   MIXER_COPY  MSS_mixer_copy;
   }
MIXSTAGE;

typedef struct
   {
   struct _FLTPROVIDER FAR *provider;
   HSAMPLESTATE             sample_state;
   }
FLTSTAGE;

typedef struct
{
   S32       active;    // Pass-through if 0, active if 1
   HPROVIDER provider;

   union
      {
      ASISTAGE ASI;
      MIXSTAGE MIX;
      FLTSTAGE FLT;
      }
   TYPE;
}
DPINFO;

//
// Other data types
//

typedef struct _AIL_INPUT_INFO        // Input descriptor type
{
   U32        device_ID;       // DS LPGUID or wave device ID
   U32        hardware_format; // e.g., DIG_F_STEREO_16
   U32        hardware_rate;   // e.g., 22050
   AILINCB    callback;        // Callback function to receive incoming data
   S32        buffer_size;     // Maximum # of bytes to be passed to callback (-1 to use DIG_INPUT_LATENCY)
   U32        user_data;       // this is a user defined value
}
AIL_INPUT_INFO;

typedef struct _AILTIMER                 // Timer instance
{
   U32      status;
   AILTIMERCB callback;
   U32      user;

   S32      elapsed;
   S32      value;
   S32      callingCT;           // Calling EXE's task number (16 bit only)
   S32      callingDS;           // Calling EXE's DS (used in 16 bit only)
   S32      IsWin32s;            // Is this a Win32s callback
} AILTIMERSTR;

typedef struct _ADPCMDATATAG
{
  U32 blocksize;
  U32 extrasamples;
  U32 blockleft;
  U32 step;
  U32 savesrc;
  U32 sample;
  U32 destend;
  U32 srcend;
  U32 samplesL;
  U32 samplesR;
  U16 moresamples[16];
} ADPCMDATA;

typedef struct _SAMPLE           // Sample instance
{
   char       tag[4];            // HSAM

   HDIGDRIVER driver;            // Driver for playback

   U32      status;              // SMP_ flags: _FREE, _DONE, _PLAYING

   void const FAR *start[2];     // Sample buffer address (W)
   U32       len  [2];           // Sample buffer size in bytes (W)
   U32       pos  [2];           // Index to next byte (R/W)
   U32       done [2];           // Nonzero if buffer with len=0 sent by app
   S32       reset_ASI [2];      // Reset the ASI decoder at the end of the buffer

   U32      src_fract;           // Fractional part of source address
   S32      left_val;            // Mixer source value from end of last buffer
   S32      right_val;           // Mixer source value from end of last buffer

   S32      current_buffer;      // Buffer # active (0/1)
   S32      last_buffer;         // Last active buffer (for double-buffering)
   S32      starved;             // Buffer stream has run out of data

   S32      loop_count;          // # of cycles-1 (1=one-shot, 0=indefinite)
   S32      loop_start;          // Starting offset of loop block (0=SOF)
   S32      loop_end;            // End offset of loop block (-1=EOF)

   S32      format;              // DIG_F format (8/16 bits, mono/stereo)
   U32      flags;               // DIG_PCM_SIGN / DIG_PCM_ORDER (stereo only)

   S32      playback_rate;       // Playback rate in hertz

   S32      volume;              // Sample volume 0-127
   S32      pan;                 // Mono panpot/stereo balance (0=L ... 127=R)

   S32      left_scale;          // Left/mono volume scalar 0-2047
   S32      right_scale;         // Right volume scalar 0-2047

   S32      service_type;        // 1 if single-buffered; 2 if streamed

   AILSAMPLECB  SOB;             // Start-of-block callback function
   AILSAMPLECB  EOB;             // End-of-buffer callback function
   AILSAMPLECB  EOS;             // End-of-sample callback function

   S32      user_data  [8];      // Miscellaneous user data
   S32      system_data[8];      // Miscellaneous system data

   ADPCMDATA adpcm;

#ifdef IS_WINDOWS

   S32      SOB_IsWin32s;        // Is this a Win32s callback
   S32      EOB_IsWin32s;        // Is this a Win32s callback
   S32      EOS_IsWin32s;        // Is this a Win32s callback

   //
   // DirectSound-specific data
   //

   S32      secondary_buffer;    // Secondary buffer index

   S32      service_interval;    // Service sample every n ms
   S32      service_tick;        // Current service countdown value
   S32      buffer_segment_size; // Buffer segment size to fill

   S32      prev_segment;        // Previous segment # (0...n)
   S32      prev_cursor;         // Previous play cursor location

   S32      bytes_remaining;     // # of bytes left to play (if not -1)

   S32      direct_control;      // 1 if app controls buffer, 0 if MSS

#endif

   S32      doeob;               // Flags to trigger callbacks
   S32      dosob;
   S32      doeos;

   //
   // Sample pipeline stages
   //

   DPINFO   pipeline[N_SAMPLE_STAGES];

   //
   // Reverb parms
   //

   F32      reverb_level;           // Level [0.0, 1.0]
   F32      reverb_reflect_time;    // Reflect time in milliseconds
   F32      reverb_decay_time;      // Decay time [0.1, 20.0]
   S32      base_scale;             // Original 12-bit volume scalar
}
SAMPLE;

#if defined(IS_WINDOWS) || defined(IS_MAC)

DXDEC  U32     AILCALL  AIL_get_timer_highest_delay   (void);

DXDEC  void         AILCALL AIL_serve(void);

#ifdef IS_MAC

typedef void * LPSTR;

#define WHDR_DONE 0

typedef struct _WAVEIN
{
  long temp;
} * HWAVEIN;

typedef struct _WAVEHDR
{
  S32  dwFlags;
  S32  dwBytesRecorded;
  S32  dwUser;
  S32  temp;
  void * lpData;
  S32  dwBufferLength;
  S32  longdwLoops;
  S32  dwLoops;
  void * lpNext;
  U32  * reserved;

} WAVEHDR, * LPWAVEHDR;

#endif

typedef struct _DIG_INPUT_DRIVER FAR *HDIGINPUT; // Handle to digital input driver

typedef struct _DIG_INPUT_DRIVER    // Handle to digital input driver
{
   C8     tag[4];                   // HDIN

   HTIMER background_timer;         // Background timer handle

   AIL_INPUT_INFO info;             // Input device descriptor
   
   S32       input_enabled;         // 1 if enabled, 0 if not

#ifndef IS_MAC

   U32          callback_user;      // Callback user value

   //
   // Provider-independent data
   //

   U32       DMA_size;              // Size of each DMA sub-buffer in bytes
   void FAR *DMA[2];                // Simulated DMA buffers

   U8        silence;               // Silence value for current format (0 or 128)

   S32       device_active;         // 1 if buffers submittable, 0 if not

   //
   // waveOut-specific data
   //

   HWAVEIN          hWaveIn;        // Handle to wave input device
   volatile WAVEHDR wavehdr[2];     // Handles to wave headers

#else
  Boolean  timer_started;
  Boolean  locked;
  Boolean  enter_lock;
  U32      saved_period;

  void*    my_vars;

  //
  // Input related
  //

  U32    input_buffer_size;
  char   * input_buffers[2];

  //
  //   Mix related
  //

  char * build_buffer;
  U32  build_buffer_size;

  //
  // Output related
  //
  struct
  {
    S8 * buffer;
    S8 * buffer_end;

    U32  size;
    S8 * right_margine;
    S8 * current_head;
    S8 * current_tail;
  } output_buffer;

  S32  mix_operation;
  S32  playback_ratio;
  U32  src_fract;
  S8 * current_head;
  S32  left_val;
  S32  right_val;

  U32  stored_sample_size;
  U32  stored_number_of_channels;

  U32  last_rw_delta;
  U32  period;

#endif
}
DIG_INPUT_DRIVER;

#endif

typedef struct _DIG_DRIVER          // Handle to digital audio driver
{
   char     tag[4];                 // HDIG

   HTIMER      backgroundtimer;     // Background timer handle

   S32         quiet;               // # of consecutive quiet sample periods

   S32         n_active_samples;    // # of samples being processed

   S32         master_volume;       // Master sample volume 0-127

   S32         DMA_rate;            // Hardware sample rate
   S32         hw_format;           // DIG_F code in use
   U32         hw_mode_flags;       // DIG_PCM_ flags for mode in use

   S32         channels_per_sample; // # of channels per sample (1 or 2)
   S32         bytes_per_channel;   // # of bytes per channel (1 or 2)
   S32         channels_per_buffer; // # of channels per half-buffer
   S32         samples_per_buffer;  // # of samples per half-buffer

   S32         playing;             // Playback active if non-zero

#ifdef IS_MAC
   U32         n_samples_allocated;
   U32         n_samples_used;
   U32         n_samples_played;
   SAMPLE      *samples;             // Pointer to SAMPLEs

   HDIGDRIVER  next;                // Pointer to next HDIGDRIVER in use
   U32         reset_works;         // TRUE if OK to do waveOutReset
   U32         request_reset;       // If nonzero, do waveOutReset ASAP
   S32         released;            // has the sound manager been released?

   ExtSoundHeader sound_header;
   SndChannelPtr  sound_channel;
   SndCallBackUPP global_callback;
   Ptr            buffers[2];
   Boolean        loaded[2];
   U32            work_buffer;
   U32            play_buffer;
   U32            load_pos;
   U32            load_size;
   Boolean        load;
   U32            start_time;
   void*          background_processor;

#else
   HSAMPLE     samples;             // Pointer to list of SAMPLEs
#endif

   S32         n_samples;           // # of SAMPLEs

   S32         build_size;          // # of bytes in build buffer
   S32    FAR *build_buffer;        // Build buffer (4 * samples_per_buffer)

   S32         system_data[8];      // Miscellaneous system data

   S32         buffer_size;         // Size of each output buffer

#ifdef IS_WINDOWS

   //
   // waveOut-specific interface data
   //

   HWAVEOUT    hWaveOut;            // Wave output driver

   U32         reset_works;         // TRUE if OK to do waveOutReset
   U32         request_reset;       // If nonzero, do waveOutReset ASAP

   LPWAVEHDR   first;               // Pointer to first WAVEHDR in chain
   S32         n_buffers;           // # of output WAVEHDRs in chain

   LPWAVEHDR volatile FAR *return_list; // Circular list of returned WAVEHDRs
   S32       volatile      return_head; // Head of WAVEHDR list (insertion point)
   S32       volatile      return_tail; // Tail of WAVEHDR list (retrieval point)


   U32         deviceid;            // id from waveout open
   PCMWAVEFORMAT  wformat;          // format from waveout open

   //
   // DirectSound-specific interface data
   //

   U32                    guid;        // The guid id of the ds driver
   AILLPDIRECTSOUND       pDS;         // DirectSound output driver (don't
                                       // use with Smacker directly anymore!)

   U32                    ds_priority; // priority opened with

   S32                    emulated_ds; // is ds emulated or not?
   AILLPDIRECTSOUNDBUFFER lppdsb;      // primary buffer or null

   U32                    dsHwnd;      // HWND used with DirectSound

   AILLPDIRECTSOUNDBUFFER FAR * lpbufflist;   // List of pointers to secondary buffers
   HSAMPLE         FAR *samp_list;      // HSAMPLE associated with each buffer
   S32             FAR *sec_format;     // DIG_F_ format for secondary buffer
   S32                  max_buffs;      // Max. allowable # of secondary buffers

   //
   // Misc. data
   //

   S32         released;            // has the sound manager been released?

   U32         foreground_timer;    // Foreground timer handle

   HDIGDRIVER  next;                // Pointer to next HDIGDRIVER in use
   S32      callingCT;              // Calling EXE's task number (16 bit only)
   S32      callingDS;              // Calling EXE's DS (used in 16 bit only)

   //
   // Vars for waveOut emulation
   //

   S32 DS_initialized;

   AILLPDIRECTSOUNDBUFFER DS_sec_buff;    // Secondary buffer (or NULL if none)
   AILLPDIRECTSOUNDBUFFER DS_out_buff;    // Output buffer (may be sec or prim)
   S32 DS_buffer_size;                    // Size of entire output buffer

   S32 DS_frag_cnt;                 // Total fragment count and size, and
   S32 DS_frag_size;                // last fragment occupied by play cursor
   S32 DS_last_frag;
   S32 DS_last_write;
   S32 DS_last_timer;
   S32 DS_skip_time;

   S32 DS_use_default_format;       // 1 to force use of default DS primary buffer format

#else

   #ifdef IS_DOS

   // must be first in the DOS section
   void       *DMA[2];              // Protected-mode pointers to half-buffers
                                    // (note that DMA[0] may != DMA_buf)


   REALFAR     DMA_seg;             // Seg:off pointer to DMA buffers (off=0)
   U32         DMA_sel;             // Selector for DMA buffers (off=0)
   void       *DMA_buf;             // Protected-mode pointer to DMA buffers

   S16        *buffer_flag;         // Protected-mode pointer to buffer flag
   S32         last_buffer;         // Last active buffer flag value in driver

   AIL_DRIVER *drvr;                // Base driver descriptor

   DIG_DDT    *DDT;                 // Protected-mode pointer to DDT
   DIG_DST    *DST;                 // Protected-mode pointer to DST
   
   #endif

#endif

#ifdef IS_X86
   S32         use_MMX;             // Use MMX with this driver if TRUE
#endif

   void   FAR *decode_buffer;       // Buffer used by optional ASI pipeline decoder
   S32         decode_buffer_size;  // # of bytes in decode buffer

   U32 us_count;
   U32 ms_count;
   U32 last_ms_polled;
   U32 last_percent;

   //
   // Digital driver pipeline stages
   //

   DPINFO   pipeline[N_DIGDRV_STAGES];

   //
   // Reverb buffer
   //

   S32 FAR *reverb_buffer;
   S32      reverb_buffer_size;
   S32      reverb_buffer_position;

#ifdef IS_WINDOWS
   S32                  no_wom_done;    // don't process WOM_DONEs on this driver
   U32                  wom_done_buffers;
#endif
}
DIG_DRIVER;

typedef struct                      // MIDI status log structure
   {
   S32      program   [NUM_CHANS];  // Program Change
   S32      pitch_l   [NUM_CHANS];  // Pitch Bend LSB
   S32      pitch_h   [NUM_CHANS];  // Pitch Bend MSB

   S32      c_lock    [NUM_CHANS];  // Channel Lock
   S32      c_prot    [NUM_CHANS];  // Channel Lock Protection
   S32      c_mute    [NUM_CHANS];  // Channel Mute
   S32      c_v_prot  [NUM_CHANS];  // Voice Protection
   S32      bank      [NUM_CHANS];  // Patch Bank Select
   S32      gm_bank_l [NUM_CHANS];  // GM Bank Select
   S32      gm_bank_m [NUM_CHANS];  // GM Bank Select
   S32      indirect  [NUM_CHANS];  // ICA indirect controller value
   S32      callback  [NUM_CHANS];  // Callback Trigger

   S32      mod       [NUM_CHANS];  // Modulation
   S32      vol       [NUM_CHANS];  // Volume
   S32      pan       [NUM_CHANS];  // Panpot
   S32      exp       [NUM_CHANS];  // Expression
   S32      sus       [NUM_CHANS];  // Sustain
   S32      reverb    [NUM_CHANS];  // Reverb
   S32      chorus    [NUM_CHANS];  // Chorus

   S32      bend_range[NUM_CHANS];  // Bender Range (data MSB, RPN 0 assumed)

   S32      RPN_L     [NUM_CHANS];  // RPN # LSB
   S32      RPN_M     [NUM_CHANS];  // RPN # MSB
   }
CTRL_LOG;

typedef struct _SEQUENCE                  // XMIDI sequence state table
{
   char     tag[4];                       // HSEQ

   HMDIDRIVER driver;                     // Driver for playback

   U32      status;                       // SEQ_ flags

   void const   FAR *TIMB;                // XMIDI IFF chunk pointers
   void const   FAR *RBRN;
   void const   FAR *EVNT;

   U8 const     FAR *EVNT_ptr;            // Current event pointer

   U8      FAR *ICA;                      // Indirect Controller Array

   AILPREFIXCB   prefix_callback;         // XMIDI Callback Prefix handler
   AILTRIGGERCB  trigger_callback;        // XMIDI Callback Trigger handler
   AILBEATCB     beat_callback;           // XMIDI beat/bar change handler
   AILSEQUENCECB EOS;                     // End-of-sequence callback function

   S32      loop_count;                   // 0=one-shot, -1=indefinite, ...

   S32      interval_count;               // # of intervals until next event
   S32      interval_num;                 // # of intervals since start

   S32      volume;                       // Sequence volume 0-127
   S32      volume_target;                // Target sequence volume 0-127
   S32      volume_accum;                 // Accumulated volume period
   S32      volume_period;                // Period for volume stepping

   S32      tempo_percent;                // Relative tempo percentage 0-100
   S32      tempo_target;                 // Target tempo 0-100
   S32      tempo_accum;                  // Accumulated tempo period
   S32      tempo_period;                 // Period for tempo stepping
   S32      tempo_error;                  // Error counter for tempo DDA

   S32      beat_count;                   // Sequence playback position
   S32      measure_count;

   S32      time_numerator;               // Sequence timing data
   S32      time_fraction;
   S32      beat_fraction;
   S32      time_per_beat;

   void const FAR *FOR_ptrs[FOR_NEST];    // Loop stack
   S32      FOR_loop_count [FOR_NEST];

   S32      chan_map       [NUM_CHANS];   // Physical channel map for sequence

   CTRL_LOG shadow;                       // Controller values for sequence

   S32      note_count;                   // # of notes "on"

   S32      note_chan      [MAX_NOTES];   // Channel for queued note (-1=free)
   S32      note_num       [MAX_NOTES];   // Note # for queued note
   S32      note_time      [MAX_NOTES];   // Remaining duration in intervals

   S32      user_data  [8];               // Miscellaneous user data
   S32      system_data[8];               // Miscellaneous system data

#ifdef IS_WINDOWS
   S32      PREFIX_IsWin32s;              // Is this a Win32s callback
   S32      TRIGGER_IsWin32s;             // Is this a Win32s callback
   S32      BEAT_IsWin32s;                // Is this a Win32s callback
   S32      EOS_IsWin32s;                 // Is this a Win32s callback
#endif
} SEQUENCE;

#ifdef IS_MAC

struct MIDIHDR;
struct MIDIOUT;
typedef struct MIDIOUT* HMIDIOUT;

#endif

typedef struct _MDI_DRIVER          // Handle to XMIDI driver
{
   char     tag[4];                 // HMDI

   HTIMER      timer;               // XMIDI quantization timer
   S32         interval_time;       // XMIDI quantization timer interval in uS

   S32         disable;             // > 0 to disable XMIDI service

   HSEQUENCE   sequences;           // Pointer to list of SEQUENCEs
   S32         n_sequences;         // # of SEQUENCEs

   S32         lock  [NUM_CHANS];   // 1 if locked, 2 if protected, else 0
   HSEQUENCE   locker[NUM_CHANS];   // HSEQUENCE which locked channel
   HSEQUENCE   owner [NUM_CHANS];   // HSEQUENCE which owned locked channel
   HSEQUENCE   user  [NUM_CHANS];   // Last sequence to use channel
   S32         state [NUM_CHANS];   // Lock state prior to being locked

   S32         notes [NUM_CHANS];   // # of active notes in channel

   AILEVENTCB  event_trap;          // MIDI event trap callback function
   AILTIMBRECB timbre_trap;         // Timbre request callback function

   S32         master_volume;       // Master XMIDI note volume 0-127

   S32         system_data[8];      // Miscellaneous system data

#if defined(IS_WINDOWS) || defined(IS_MAC)
   
   S32         released;            // has the hmidiout handle been released
   U32         deviceid;            // ID of the MIDI device
   U8      FAR *sysdata;            // SysEx buffer

#endif

#ifdef IS_WINDOWS

   S32      EVENT_IsWin32s;         // Is this a Win32s callback
   S32      TIMBRE_IsWin32s;        // Is this a Win32s callback

   MIDIHDR FAR *mhdr;               // SysEx header

   HMDIDRIVER  next;                // Pointer to next HMDIDRIVER in use
   S32      callingCT;              // Calling EXE's task number (16 bit only)
   S32      callingDS;              // Calling EXE's DS (used in 16 bit only)

   HMIDIOUT    hMidiOut;            // MIDI output driver

#else

   #ifdef IS_DOS

   S32        message_count;       // MIDI message count
   S32        offset;              // MIDI buffer offset

   AIL_DRIVER *drvr;               // Base driver descriptor

   MDI_DDT    *DDT;                // Protected-mode pointer to DDT
   MDI_DST    *DST;                // Protected-mode pointer to DST
   #else
     #ifdef IS_MAC
       struct MIDIHDR FAR *mhdr;               // SysEx header
       HMDIDRIVER  next;                // Pointer to next HMDIDRIVER in use
       HMIDIOUT    hMidiOut;            // MIDI output driver
       U32      last_us_time;
       long     period_counter;
       long     current_period_sum;
     #endif
   #endif

#endif

}
MDI_DRIVER;

typedef struct                      // XMIDI TIMB IFF chunk
   {
   S8    name[4];

   U8    msb;
   U8    lsb;
   U8    lsb2;
   U8    lsb3;

   U16   n_entries;

   U16   timbre[1];
   }
TIMB_chunk;

typedef struct                      // XMIDI RBRN IFF entry
   {
   S16   bnum;
   U32   offset;
   }
RBRN_entry;

typedef struct                      // Wave library entry
{
   S32   bank;                      // XMIDI bank, MIDI patch for sample
   S32   patch;

   S32   root_key;                  // Root MIDI note # for sample (or -1)

   U32   file_offset;               // Offset of wave data from start-of-file
   U32   size;                      // Size of wave sample in bytes

   S32   format;                    // DIG_F format (8/16 bits, mono/stereo)
   U32   flags;                     // DIG_PCM_SIGN / DIG_PCM_ORDER (stereo)
   S32   playback_rate;             // Playback rate in hertz
}
WAVE_ENTRY;

typedef struct                      // Virtual "wave synthesizer" descriptor
{
   HMDIDRIVER mdi;                  // MIDI driver for use with synthesizer
   HDIGDRIVER dig;                  // Digital driver for use with synthesizer

   WAVE_ENTRY FAR *library;         // Pointer to wave library

   AILEVENTCB  prev_event_fn;       // Previous MIDI event trap function
   AILTIMBRECB prev_timb_fn;        // Previous timbre request trap function

   CTRL_LOG    controls;            // MIDI controller states

   WAVE_ENTRY FAR *wave [NUM_CHANS];// Pointer to WAVE_ENTRY for each channel

   HSAMPLE     S    [MAX_W_VOICES]; // List of HSAMPLE voices
   S32         n_voices;            // Actual # of voices allocated to synth

   S32         chan [MAX_W_VOICES]; // MIDI channel for each voice, or -1
   S32         note [MAX_W_VOICES]; // MIDI note number for voice
   S32         root [MAX_W_VOICES]; // MIDI root note for voice
   S32         rate [MAX_W_VOICES]; // Playback rate for voice
   S32         vel  [MAX_W_VOICES]; // MIDI note velocity for voice
   U32         time [MAX_W_VOICES]; // Timestamp for voice

   U32         event;               // Event counter for LRU timestamps
}
WAVE_SYNTH;

typedef WAVE_SYNTH FAR * HWAVESYNTH;// Handle to virtual wave synthesizer

//
// Handle to thread which called AIL_startup()
//
// This thread is suspended by MSS callback threads, to simulate DOS-style
// interrupt handler behavior
//

#ifdef IS_WIN32

extern HANDLE hAppThread;

#endif

//
// Background flag for timers
//

extern volatile S32   AIL_bkgnd_flag;

//
// Global preference array
//

extern S32            AIL_preference   [N_PREFS];

//
// DIG_DRIVER list
//

extern HDIGDRIVER     DIG_first;

//
// MDI_DRIVER list
//

extern HMDIDRIVER     MDI_first;

//
// Miscellaneous system services
//

#define FILE_READ_WITH_SIZE ((void FAR*)(S32)-1)

#ifndef NO_OLD_SYS_FUNCTIONS

#define MEM_alloc_lock AIL_mem_alloc_lock
#define MEM_free_lock  AIL_mem_free_lock
#define FILE_error     AIL_file_error
#define FILE_size      AIL_file_size
#define FILE_read      AIL_file_read
#define FILE_write     AIL_file_write

#ifdef IS_DOS

#define MEM_alloc        AIL_mem_alloc
#define MEM_free         AIL_mem_free
#define MEM_use_malloc   AIL_mem_use_malloc
#define MEM_use_free     AIL_mem_use_free
#define MEM_alloc_DOS    AIL_mem_alloc_DOS
#define MEM_free_DOS     AIL_mem_free_DOS
#define VMM_lock_range   AIL_vmm_lock_range
#define VMM_unlock_range AIL_vmm_unlock_range
#define VMM_lock         AIL_vmm_lock
#define VMM_unlock       AIL_vmm_unlock

#endif

#endif

extern S32 AILCALLBACK DP_ASI_DECODER_callback(U32       user,
                                               void FAR *dest,
                                               S32       bytes_requested,
                                               S32       offset);

DXDEC  void FAR * AILCALL AIL_mem_alloc_lock(U32       size);
DXDEC  void       AILCALL AIL_mem_free_lock (void FAR *ptr);

DXDEC  S32        AILCALL AIL_file_error   (void);

DXDEC  S32        AILCALL AIL_file_size    (char const FAR  *filename);

DXDEC  void FAR * AILCALL AIL_file_read    (char const FAR   *filename,
                                           void FAR *dest);

DXDEC  S32        AILCALL AIL_file_write   (char const FAR    *filename,
                                            void const FAR  *buf,
                                            U32       len);

DXDEC  S32        AILCALL AIL_WAV_file_write
                                           (char const FAR    *filename,
                                            void const FAR  *buf,
                                            U32       len,
                                            S32       rate,
                                            S32       format);

DXDEC  S32        AILCALL AIL_file_append  (char const FAR *filename,
                                            void const FAR *buf, U32 len);

#ifdef IS_MAC


DXDEC  S32        AILCALL AIL_file_fss_size(FSSpec const FAR  *filename);

DXDEC  void FAR * AILCALL AIL_file_fss_read(FSSpec const FAR   *filename,
                                            void FAR *dest);

DXDEC  S32        AILCALL AIL_file_fss_write(FSSpec const FAR    *filename,
                                             void const FAR  *buf,
                                             U32       len);

DXDEC  S32        AILCALL AIL_file_fss_attrib_write
                                            (FSSpec const FAR    *filename,
                                             void const FAR  *buf,
                                             U32       len,
                                             U32       type,
                                             U32       creator );

DXDEC  S32        AILCALL AIL_WAV_file_fss_write
                                           (FSSpec const FAR    *filename,
                                            void const FAR  *buf,
                                            U32       len,
                                            S32       rate,
                                            S32       format);

DXDEC void * AILCALL AIL_mem_use_malloc(void * AILCALLBACK (*fn)(U32));
DXDEC void * AILCALL AIL_mem_use_free  (void AILCALLBACK (*fn)(void *));

#endif

#ifdef IS_DOS

extern void * AILCALLBACK (*AIL_mem_alloc) (U32);
extern void   AILCALLBACK (*AIL_mem_free)  (void *);

void * cdecl AIL_mem_use_malloc(void * AILCALLBACK (*fn)(U32));
void * cdecl AIL_mem_use_free  (void AILCALLBACK (*fn)(void *));

//
// Other memory-management functions
//

DXDEC  S32   AILCALL AIL_mem_alloc_DOS (U32  n_paras,
                                        void **protected_ptr,
                                        U32 *segment_far_ptr,
                                        U32 *selector);

DXDEC  void  AILCALL AIL_mem_free_DOS (void  *protected_ptr,
                                       U32  segment_far_ptr,
                                       U32  selector);

DXDEC  S32   AILCALL AIL_vmm_lock_range   (void  *p1, void *p2);
DXDEC  S32   AILCALL AIL_vmm_unlock_range (void  *p1, void *p2);

DXDEC  S32   AILCALL AIL_vmm_lock         (void  *start, U32 size);
DXDEC  S32   AILCALL AIL_vmm_unlock       (void  *start, U32 size);

DXDEC  U32  AILCALL AIL_sel_base         (U32  sel);

DXDEC  void   AILCALL AIL_sel_set_limit  (U32  sel,
                                          U32  limit);
//
// Last IO_PARMS structure used to attempt device detection
//

extern IO_PARMS       AIL_last_IO_attempt;

//
// Low-level support services
//

DXDEC REALFAR AILCALL  AIL_get_real_vect            (U32       vectnum);

DXDEC void    AILCALL  AIL_set_real_vect            (U32       vectnum,
                                                     REALFAR   real_ptr);

DXDEC void    AILCALL  AIL_set_USE16_ISR            (S32        IRQ,
                                                     REALFAR    real_base,
                                                     U32        ISR_offset);

DXDEC void    AILCALL  AIL_restore_USE16_ISR        (S32        IRQ);

DXDEC U32     AILCALL  AIL_disable_interrupts       (void);
DXDEC void    AILCALL  AIL_restore_interrupts       (U32        FD_register);

DXDEC void    AILCALL  AIL_switch_stack             (void       *stack,
                                                     U32        size,
                                                     U32        *SS,
                                                     void       **ESP,
                                                     void       **EBP);

DXDEC void    AILCALL  AIL_restore_stack            (U32        SS,
                                                     void       *ESP,
                                                     void       *EBP);

DXDEC S32     AILCALL  AIL_call_driver              (AIL_DRIVER *drvr,
                                                     S32        fn,
                                                     VDI_CALL   *in,
                                                     VDI_CALL   *out);

DXDEC S32     AILCALL  AIL_read_INI                 (AIL_INI    *INI,
                                                     char       *filename);

DXDEC U32     AILCALL  AIL_interrupt_divisor        (void);

#endif


#ifdef __WATCOMC__

void MSSBreakPoint();
#pragma aux MSSBreakPoint = "int 3";

#else

#define MSSBreakPoint() __asm {int 3}

#endif


//
// High-level support services
//

#ifdef IS_MAC

#if !defined(max)
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(min)
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#endif

#ifdef IS_DOS

#ifdef IS_WATCOM

#if !defined(max) // Watcom stdlib.h doesn't define these for C++
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(min)
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#endif

#ifdef __SW_3R
extern S32 AILCALL AIL_startup_reg               (void);
#define AIL_startup AIL_startup_reg
#else
extern S32 AILCALL AIL_startup_stack             (void);
#define AIL_startup AIL_startup_stack
#endif

#define AIL_quick_startup(ud,um,opr,opb,ops) AIL_quick_startup_with_start(&AIL_startup,ud,um,opr,opb,ops)

#define AIL_get_preference(number) (AIL_preference[number])

#else

DXDEC  S32     AILCALL  AIL_startup                   (void);

DXDEC  S32     AILCALL  AIL_get_preference            (U32         number);

#endif

DXDEC  void    AILCALL  AIL_shutdown                  (void);

DXDEC  S32     AILCALL  AIL_set_preference            (U32         number,
                                                      S32          value);

DXDEC char FAR *AILCALL  AIL_last_error                (void);

DXDEC  void    AILCALL  AIL_set_error                 (char const FAR * error_msg);

//
// Low-level support services
//

DXDEC  void    
#ifndef IS_MAC
__cdecl
#endif
AIL_debug_printf              (C8 const FAR *fmt, ...);

#ifdef IS_X86

DXDEC  U32     AILCALL  AIL_MMX_available             (void);

#endif

DXDEC  void    AILCALL  AIL_lock                      (void);
DXDEC  void    AILCALL  AIL_unlock                    (void);

#ifdef IS_WIN32

DXDEC  void    AILCALL  AIL_lock_mutex                (void);
DXDEC  void    AILCALL  AIL_unlock_mutex              (void);

#endif

DXDEC  void    AILCALL  AIL_delay                     (S32         intervals);

DXDEC  S32     AILCALL  AIL_background                (void);

//
// Process services
//

DXDEC  HTIMER  AILCALL  AIL_register_timer            (AILTIMERCB  fn);

DXDEC  U32     AILCALL  AIL_set_timer_user            (HTIMER      timer,
                                                      U32         user);

DXDEC  void    AILCALL  AIL_set_timer_period          (HTIMER      timer,
                                                      U32         microseconds);

DXDEC  void    AILCALL  AIL_set_timer_frequency       (HTIMER      timer,
                                                      U32         hertz);

DXDEC  void    AILCALL  AIL_set_timer_divisor         (HTIMER      timer,
                                                      U32         PIT_divisor);

DXDEC  void    AILCALL  AIL_start_timer               (HTIMER      timer);
DXDEC  void    AILCALL  AIL_start_all_timers          (void);

DXDEC  void    AILCALL  AIL_stop_timer                (HTIMER      timer);
DXDEC  void    AILCALL  AIL_stop_all_timers           (void);

DXDEC  void    AILCALL  AIL_release_timer_handle      (HTIMER      timer);
DXDEC  void    AILCALL  AIL_release_all_timers        (void);

#ifdef IS_WIN32

#ifndef BUILD_MSS

// static function that handles shutdown
int __cdecl MSS_auto_cleanup(void);

#ifdef _MSC_VER
// on MSVC, automatically register a cleanup function
//ODCODENOTE Remove
//#define AIL_startup() (MSS_auto_cleanup(),AIL_startup())
#endif

#endif

DXDEC  HWND    AILCALL  AIL_HWND                      (void);

#else
  #ifdef IS_MAC
    DXDEC ProcessSerialNumber AIL_Process(void);
  #endif
#endif

//
// high-level digital services
//

DXDEC HDIGDRIVER AILCALL AIL_open_digital_driver( U32 frequency,
                                                  S32 bits,
                                                  S32 channel,
                                                  U32 flags );

#define AIL_OPEN_DIGITAL_FORCE_PREFERENCE 1

DXDEC void AILCALL AIL_close_digital_driver( HDIGDRIVER dig );

#ifdef IS_WINDOWS

#define AIL_MSS_version(str,len)        \
{                                       \
  HINSTANCE l=LoadLibrary(MSSDLLNAME);  \
  if ((U32)l<=32)                       \
    *(str)=0;                           \
  else {                                \
    LoadString(l,1,str,len);            \
    FreeLibrary(l);                     \
  }                                     \
}

DXDEC  S32          AILCALL AIL_waveOutOpen          (HDIGDRIVER   FAR *drvr,
                                                      LPHWAVEOUT   FAR  *lphWaveOut,
                                                      S32             wDeviceID,
                                                      LPWAVEFORMAT      lpFormat);

DXDEC  void         AILCALL AIL_waveOutClose          (HDIGDRIVER drvr);

DXDEC  S32          AILCALL AIL_digital_handle_release(HDIGDRIVER drvr);

DXDEC  S32          AILCALL AIL_digital_handle_reacquire
                                                     (HDIGDRIVER drvr);

#else

#ifdef IS_MAC

typedef struct MSS_VersionType_
{
  Str255 version_name;
} MSS_VersionType;

#define AIL_MSS_version(str,len)                        \
{                                                       \
  long _res = OpenResFile("\pMiles Shared Library");    \
  if (_res==-1)                                         \
  {                                                     \
    str[0]=0;                                           \
  }                                                     \
  else                                                  \
  {                                                     \
    Handle _H;                                          \
    short _Err;                                         \
    long _cur= CurResFile();                            \
    UseResFile(_res);                                   \
    _H = GetResource('vers', 2);                        \
    _Err = ResError();                                  \
    if((_Err != noErr) || (_H==0))                      \
    {                                                   \
      str[0]=0;                                         \
      UseResFile(_cur);                                 \
      CloseResFile(_res);                               \
    }                                                   \
    else                                                \
    {                                                   \
      if (GetHandleSize(_H)==0)                         \
      {                                                 \
        str[0]=0;                                       \
        UseResFile(_cur);                               \
        CloseResFile(_res);                             \
      }                                                 \
      else                                              \
      {                                                 \
        MSS_VersionType * _vt = (MSS_VersionType*)*_H;  \
        if ((U32)_vt->version_name[6]>4)                \
          _vt->version_name[6]-=4;                      \
        else                                            \
          _vt->version_name[6]=0;                       \
        if (((U32)len) <= ((U32)_vt->version_name[6]))  \
          _vt->version_name[6] = (U8)len-1;             \
        memcpy( str, _vt->version_name+11, _vt->version_name[6] ); \
        str[_vt->version_name[6]]=0;                    \
        UseResFile(_cur);                               \
        CloseResFile(_res);                             \
      }                                                 \
      ReleaseResource(_H);                              \
    }                                                   \
  }                                                     \
}

DXDEC  S32          AILCALL AIL_digital_handle_release(HDIGDRIVER drvr);

DXDEC  S32          AILCALL AIL_digital_handle_reacquire
                                                     (HDIGDRIVER drvr);

#else

//
// DOS installation services
//

DXDEC IO_PARMS *   AILCALL AIL_get_IO_environment    (AIL_DRIVER *drvr);

DXDEC AIL_DRIVER*  AILCALL AIL_install_driver        (U8 const     *driver_image,
                                                      U32       n_bytes);

DXDEC void         AILCALL AIL_uninstall_driver      (AIL_DRIVER *drvr);

DXDEC S32         AILCALL AIL_install_DIG_INI       (HDIGDRIVER *dig);

DXDEC HDIGDRIVER   AILCALL AIL_install_DIG_driver_file
                                                    (char const *filename,
                                                     IO_PARMS   *IO);

DXDEC void         AILCALL AIL_uninstall_DIG_driver  (HDIGDRIVER  dig);


DXDEC HDIGDRIVER   AILCALL AIL_install_DIG_driver_image
                                                    (void const    *driver_image,
                                                     U32     size,
                                                     IO_PARMS *IO);
#endif
#endif

DXDEC char FAR*     AILCALL AIL_set_redist_directory(char const FAR*dir);

DXDEC  S32          AILCALL AIL_digital_CPU_percent   (HDIGDRIVER dig);

DXDEC  S32          AILCALL AIL_digital_latency       (HDIGDRIVER dig);

DXDEC  HSAMPLE      AILCALL AIL_allocate_sample_handle
                                                      (HDIGDRIVER dig);

DXDEC  HSAMPLE      AILCALL AIL_allocate_file_sample  (HDIGDRIVER dig,
                                                       void const       FAR *file_image,
                                                       S32         block);

DXDEC  void         AILCALL AIL_release_sample_handle (HSAMPLE S);

DXDEC  void         AILCALL AIL_init_sample           (HSAMPLE S);

DXDEC  S32          AILCALL AIL_set_sample_file       (HSAMPLE   S,
                                                       void const FAR *file_image,
                                                       S32       block);

DXDEC  S32          AILCALL AIL_set_named_sample_file (HSAMPLE   S,
                                                       C8 const   FAR *file_type_suffix,
                                                       void const FAR *file_image,
                                                       S32       file_size,
                                                       S32       block);

DXDEC  HPROVIDER    AILCALL AIL_set_sample_processor  (HSAMPLE     S,
                                                       SAMPLESTAGE pipeline_stage,
                                                       HPROVIDER   provider);

DXDEC  HPROVIDER    AILCALL AIL_set_digital_driver_processor
                                                      (HDIGDRIVER  dig,
                                                       DIGDRVSTAGE pipeline_stage,
                                                       HPROVIDER   provider);

DXDEC  void         AILCALL AIL_set_sample_adpcm_block_size
                                                     (HSAMPLE S,
                                                     U32     blocksize);

DXDEC  void         AILCALL AIL_set_sample_address    (HSAMPLE S,
                                                     void const   FAR *start,
                                                     U32     len);

DXDEC  void         AILCALL AIL_set_sample_type       (HSAMPLE S,
                                                     S32     format,
                                                     U32     flags);

DXDEC  void         AILCALL AIL_start_sample          (HSAMPLE S);

DXDEC  void         AILCALL AIL_stop_sample           (HSAMPLE S);

DXDEC  void         AILCALL AIL_resume_sample         (HSAMPLE S);

DXDEC  void         AILCALL AIL_end_sample            (HSAMPLE S);

DXDEC  void         AILCALL AIL_set_sample_playback_rate
                                                     (HSAMPLE S,
                                                     S32     playback_rate);

DXDEC  void         AILCALL AIL_set_sample_volume     (HSAMPLE S,
                                                     S32     volume);

DXDEC  void         AILCALL AIL_set_sample_pan        (HSAMPLE S,
                                                     S32     pan);

DXDEC  void         AILCALL AIL_set_sample_loop_count (HSAMPLE S,
                                                     S32     loop_count);

DXDEC  void         AILCALL AIL_set_sample_loop_block (HSAMPLE S,
                                                     S32     loop_start_offset,
                                                     S32     loop_end_offset);

DXDEC  U32          AILCALL AIL_sample_status         (HSAMPLE S);

DXDEC  S32          AILCALL AIL_sample_playback_rate  (HSAMPLE S);

DXDEC  S32          AILCALL AIL_sample_volume         (HSAMPLE S);

DXDEC  S32          AILCALL AIL_sample_pan            (HSAMPLE S);

DXDEC  S32          AILCALL AIL_sample_loop_count     (HSAMPLE S);

DXDEC  void         AILCALL AIL_set_digital_master_volume
                                                     (HDIGDRIVER dig,
                                                     S32         master_volume);

DXDEC  S32          AILCALL AIL_digital_master_volume (HDIGDRIVER dig);

DXDEC  void         AILCALL AIL_set_sample_reverb(HSAMPLE S,
                                                        F32     reverb_level,
                                                        F32     reverb_reflect_time,
                                                        F32     reverb_decay_time);

DXDEC  void         AILCALL AIL_sample_reverb    (HSAMPLE S,
                                                        F32 FAR *reverb_level,
                                                        F32 FAR *reverb_reflect_time,
                                                        F32 FAR *reverb_decay_time);

//
// low-level digital services
//

DXDEC  S32      AILCALL AIL_minimum_sample_buffer_size(HDIGDRIVER dig,
                                                     S32         playback_rate,
                                                     S32         format);

DXDEC  S32      AILCALL AIL_sample_buffer_ready      (HSAMPLE S);

DXDEC  void     AILCALL AIL_load_sample_buffer       (HSAMPLE S,
                                                     U32     buff_num,
                                                     void const   FAR *buffer,
                                                     U32     len);

DXDEC  void     AILCALL AIL_request_EOB_ASI_reset   (HSAMPLE S,
                                                     U32     buff_num);

DXDEC  S32      AILCALL AIL_sample_buffer_info      (HSAMPLE S, //)
                                                    U32     FAR *pos0,
                                                    U32     FAR *len0,
                                                    U32     FAR *pos1,
                                                    U32     FAR *len1);

DXDEC  U32      AILCALL AIL_sample_granularity      (HSAMPLE S);

DXDEC  void     AILCALL AIL_set_sample_position      (HSAMPLE S,
                                                      U32     pos);

DXDEC  U32      AILCALL AIL_sample_position          (HSAMPLE S);

DXDEC  AILSAMPLECB AILCALL AIL_register_SOB_callback
                                                    (HSAMPLE S,
                                                     AILSAMPLECB SOB);

DXDEC  AILSAMPLECB AILCALL AIL_register_EOB_callback
                                                    (HSAMPLE S,
                                                     AILSAMPLECB EOB);

DXDEC  AILSAMPLECB AILCALL AIL_register_EOS_callback
                                                    (HSAMPLE S,
                                                     AILSAMPLECB EOS);

DXDEC  AILSAMPLECB AILCALL AIL_register_EOF_callback
                                                    (HSAMPLE S,
                                                     AILSAMPLECB EOFILE);

DXDEC  void     AILCALL AIL_set_sample_user_data   (HSAMPLE S,
                                                     U32     index,
                                                     S32     value);

DXDEC  S32      AILCALL AIL_sample_user_data       (HSAMPLE S,
                                                     U32     index);

DXDEC  S32      AILCALL AIL_active_sample_count    (HDIGDRIVER dig);

DXDEC  void     AILCALL AIL_digital_configuration  (HDIGDRIVER dig,
                                                      S32   FAR *rate,
                                                      S32   FAR *format,
                                                      char  FAR *string);
#ifdef IS_WIN32

DXDEC  S32      AILCALL AIL_set_direct_buffer_control (HSAMPLE S,
                                                     U32      command);

DXDEC  void     AILCALL AIL_get_DirectSound_info  (HSAMPLE              S,
                                                   AILLPDIRECTSOUND    *lplpDS,
                                                   AILLPDIRECTSOUNDBUFFER *lplpDSB);

DXDEC  S32      AILCALL AIL_set_DirectSound_HWND(HDIGDRIVER dig, HWND wnd);

#endif

DXDEC  void     AILCALL AIL_set_sample_ms_position (HSAMPLE    S, //)
                                                    S32        milliseconds);

DXDEC  void     AILCALL AIL_sample_ms_position     (HSAMPLE    S, //)
                                                    S32 FAR *  total_milliseconds,
                                                    S32 FAR *  current_milliseconds);


//
// Digital input services
//

#if defined(IS_WINDOWS) || defined (IS_MAC)

DXDEC HDIGINPUT AILCALL AIL_open_input             (AIL_INPUT_INFO FAR *info);

DXDEC void      AILCALL AIL_close_input            (HDIGINPUT         dig);

DXDEC AIL_INPUT_INFO FAR *
                AILCALL AIL_get_input_info         (HDIGINPUT         dig);

DXDEC S32       AILCALL AIL_set_input_state        (HDIGINPUT         dig,
                                                    S32               enable);
#endif


//
// High-level XMIDI services
//

DXDEC HMDIDRIVER AILCALL AIL_open_XMIDI_driver( U32 flags );

#define AIL_OPEN_XMIDI_NULL_DRIVER 1

DXDEC void AILCALL AIL_close_XMIDI_driver( HMDIDRIVER mdi );

#ifdef IS_MAC

DXDEC  S32          AILCALL AIL_MIDI_handle_release
                                                 (HMDIDRIVER mdi);

DXDEC  S32          AILCALL AIL_MIDI_handle_reacquire
                                                 (HMDIDRIVER mdi);

#else

#ifdef IS_WINDOWS

DXDEC  S32          AILCALL AIL_midiOutOpen(HMDIDRIVER FAR *drvr,
                                            LPHMIDIOUT FAR *lphMidiOut,
                                            S32           dwDeviceID);

DXDEC  void         AILCALL AIL_midiOutClose      (HMDIDRIVER mdi);

DXDEC  S32          AILCALL AIL_MIDI_handle_release
                                                 (HMDIDRIVER mdi);

DXDEC  S32          AILCALL AIL_MIDI_handle_reacquire
                                                 (HMDIDRIVER mdi);

#else

#ifdef IS_DOS

DXDEC S32         AILCALL AIL_install_MDI_INI       (HMDIDRIVER *mdi);

DXDEC HMDIDRIVER   AILCALL AIL_install_MDI_driver_file
                                                    (char const *filename,
                                                     IO_PARMS   *IO);

DXDEC void         AILCALL AIL_uninstall_MDI_driver  (HMDIDRIVER  mdi);


DXDEC HMDIDRIVER   AILCALL AIL_install_MDI_driver_image
                                                    (void const *driver_image,
                                                     U32       size,
                                                     IO_PARMS   *IO);

DXDEC S32     AILCALL AIL_MDI_driver_type           (HMDIDRIVER  mdi);

DXDEC void    AILCALL AIL_set_GTL_filename_prefix   (char const*prefix);

DXDEC S32     AILCALL AIL_timbre_status             (HMDIDRIVER  mdi,
                                                     S32        bank,
                                                     S32        patch);

DXDEC S32     AILCALL AIL_install_timbre            (HMDIDRIVER  mdi,
                                                     S32        bank,
                                                     S32        patch);

DXDEC void    AILCALL AIL_protect_timbre            (HMDIDRIVER  mdi,
                                                     S32        bank,
                                                     S32        patch);

DXDEC void    AILCALL AIL_unprotect_timbre          (HMDIDRIVER  mdi,
                                                     S32        bank,
                                                     S32        patch);

#endif

#endif

#endif

DXDEC  HSEQUENCE    AILCALL AIL_allocate_sequence_handle
                                                     (HMDIDRIVER mdi);

DXDEC  void         AILCALL AIL_release_sequence_handle
                                                     (HSEQUENCE S);

DXDEC  S32          AILCALL AIL_init_sequence         (HSEQUENCE S,
                                                     void const     FAR *start,
                                                     S32       sequence_num);

DXDEC  void         AILCALL AIL_start_sequence        (HSEQUENCE S);

DXDEC  void         AILCALL AIL_stop_sequence         (HSEQUENCE S);

DXDEC  void         AILCALL AIL_resume_sequence       (HSEQUENCE S);

DXDEC  void         AILCALL AIL_end_sequence          (HSEQUENCE S);

DXDEC  void         AILCALL AIL_set_sequence_tempo    (HSEQUENCE S,
                                                     S32       tempo,
                                                     S32       milliseconds);

DXDEC  void         AILCALL AIL_set_sequence_volume   (HSEQUENCE S,
                                                     S32       volume,
                                                     S32       milliseconds);

DXDEC  void         AILCALL AIL_set_sequence_loop_count
                                                     (HSEQUENCE S,
                                                     S32       loop_count);

DXDEC  U32          AILCALL AIL_sequence_status       (HSEQUENCE S);

DXDEC  S32          AILCALL AIL_sequence_tempo        (HSEQUENCE S);

DXDEC  S32          AILCALL AIL_sequence_volume       (HSEQUENCE S);

DXDEC  S32          AILCALL AIL_sequence_loop_count   (HSEQUENCE S);

DXDEC  void         AILCALL AIL_set_XMIDI_master_volume
                                                     (HMDIDRIVER mdi,
                                                     S32         master_volume);

DXDEC  S32          AILCALL AIL_XMIDI_master_volume   (HMDIDRIVER mdi);


//
// Low-level XMIDI services
//

DXDEC  S32      AILCALL AIL_active_sequence_count     (HMDIDRIVER mdi);

DXDEC  S32      AILCALL AIL_controller_value          (HSEQUENCE S,
                                                      S32       channel,
                                                      S32       controller_num);

DXDEC  S32      AILCALL AIL_channel_notes             (HSEQUENCE S,
                                                      S32       channel);

DXDEC  void     AILCALL AIL_sequence_position         (HSEQUENCE S,
                                                      S32      FAR *beat,
                                                      S32      FAR *measure);

DXDEC  void     AILCALL AIL_branch_index              (HSEQUENCE  S,
                                                      U32        marker);

DXDEC  AILPREFIXCB AILCALL AIL_register_prefix_callback
                                                     (HSEQUENCE  S,
                                                      AILPREFIXCB callback);

DXDEC  AILTRIGGERCB AILCALL AIL_register_trigger_callback
                                                     (HSEQUENCE  S,
                                                      AILTRIGGERCB callback);

DXDEC  AILSEQUENCECB AILCALL AIL_register_sequence_callback
                                                     (HSEQUENCE  S,
                                                      AILSEQUENCECB callback);

DXDEC  AILBEATCB AILCALL AIL_register_beat_callback   (HSEQUENCE  S,
                                                      AILBEATCB callback);

DXDEC  AILEVENTCB AILCALL AIL_register_event_callback (HMDIDRIVER mdi,
                                                      AILEVENTCB callback);

DXDEC  AILTIMBRECB AILCALL AIL_register_timbre_callback
                                                     (HMDIDRIVER mdi,
                                                      AILTIMBRECB callback);

DXDEC  void     AILCALL AIL_set_sequence_user_data    (HSEQUENCE S,
                                                      U32       index,
                                                      S32       value);

DXDEC  S32      AILCALL AIL_sequence_user_data        (HSEQUENCE S,
                                                      U32       index);

DXDEC  void     AILCALL AIL_register_ICA_array        (HSEQUENCE S,
                                                      U8       FAR *array);

DXDEC  S32      AILCALL AIL_lock_channel              (HMDIDRIVER mdi);

DXDEC  void     AILCALL AIL_release_channel           (HMDIDRIVER mdi,
                                                      S32         channel);

DXDEC  void     AILCALL AIL_map_sequence_channel      (HSEQUENCE S,
                                                      S32       seq_channel,
                                                      S32       new_channel);

DXDEC  S32      AILCALL AIL_true_sequence_channel     (HSEQUENCE S,
                                                      S32       seq_channel);

DXDEC  void     AILCALL AIL_send_channel_voice_message
                                                     (HMDIDRIVER  mdi,
                                                      HSEQUENCE   S,
                                                      S32         status,
                                                      S32         data_1,
                                                      S32         data_2);

DXDEC  void     AILCALL AIL_send_sysex_message        (HMDIDRIVER mdi,
                                                       void const       FAR *buffer);

DXDEC  HWAVESYNTH
                AILCALL AIL_create_wave_synthesizer   (HDIGDRIVER dig,
                                                    HMDIDRIVER mdi,
                                                       void const       FAR *wave_lib,
                                                       S32         polyphony);

DXDEC  void     AILCALL AIL_destroy_wave_synthesizer  (HWAVESYNTH W);

DXDEC  void     AILCALL AIL_set_sequence_ms_position  (HSEQUENCE S, //)
                                                       S32       milliseconds);

DXDEC  void     AILCALL AIL_sequence_ms_position(HSEQUENCE S, //)
                                                 S32 FAR *total_milliseconds,
                                                 S32 FAR *current_milliseconds);



//
// red book functions
//

#ifdef IS_DOS
typedef struct _REDBOOKTRACKINFO {
  U32 tracks;
  U32 trackstarts[100];
} REDBOOKTRACKINFO;
#endif

typedef struct _REDBOOK {
  U32 DeviceID;
  U32 paused;
  U32 pausedsec;
  U32 lastendsec;
#ifdef IS_DOS
  U32 readcontents;
  REDBOOKTRACKINFO info;
#endif
#ifdef IS_MAC
  short vDRefNum;
#endif
} REDBOOK;

typedef struct _REDBOOK FAR* HREDBOOK;

#define REDBOOK_ERROR    0
#define REDBOOK_PLAYING  1
#define REDBOOK_PAUSED   2
#define REDBOOK_STOPPED  3


DXDEC  HREDBOOK   AILCALL AIL_redbook_open(U32 which);

#ifdef IS_MAC
DXDEC  HREDBOOK   AILCALL AIL_redbook_open_volume(char const * drive);
#else
DXDEC  HREDBOOK   AILCALL AIL_redbook_open_drive(S32 drive);
#endif

DXDEC  void       AILCALL AIL_redbook_close(HREDBOOK hand);

DXDEC  void       AILCALL AIL_redbook_eject(HREDBOOK hand);

DXDEC  void       AILCALL AIL_redbook_retract(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_status(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_tracks(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_track(HREDBOOK hand);

DXDEC  void       AILCALL AIL_redbook_track_info(HREDBOOK hand,U32 tracknum,
                                                     U32 FAR* startmsec,U32 FAR* endmsec);

DXDEC  U32        AILCALL AIL_redbook_id(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_position(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_play(HREDBOOK hand,U32 startmsec, U32 endmsec);

DXDEC  U32        AILCALL AIL_redbook_stop(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_pause(HREDBOOK hand);

DXDEC  U32        AILCALL AIL_redbook_resume(HREDBOOK hand);

DXDEC  S32        AILCALL AIL_redbook_volume(HREDBOOK hand);

DXDEC  S32        AILCALL AIL_redbook_set_volume(HREDBOOK hand, S32 volume);

#ifdef IS_WIN16
  #define AIL_ms_count timeGetTime
  DXDEC U32 AILCALL AIL_us_count(void);
#else
  DXDEC U32 AILCALL AIL_ms_count(void);
  DXDEC U32 AILCALL AIL_us_count(void);
#endif


typedef struct _STREAM FAR* HSTREAM;           // Handle to stream

typedef void (AILCALLBACK FAR* AILSTREAMCB)   (HSTREAM stream);

typedef struct _STREAM {

  S32 block_oriented; // 1 if this is an ADPCM or ASI-compressed stream
  S32 using_ASI;      // 1 if using ASI decoder to uncompress stream data
  ASISTAGE FAR *ASI;  // handy pointer to our ASI coded

  HSAMPLE samp;       // the sample handle

  U32 fileh;          // the open file handle

  U8 FAR* bufs[3];    // the data buffers
  U32 bufsizes[3];    // the size of each buffer
  S32 reset_ASI[3];   // should we reset the ASI at the end of the buffer?
  S32 bufstart[3];    // offset of where this buffer started
  void FAR* asyncs[3];// async read structures

  S32 loadedbufstart[2]; // offset of where the loaded buffer started
  S32 loadedorder[2]; // order of the buffers as they were loaded
  S32 loadorder;      // incremented as each buffer is loaded

  S32 bufsize;        // size of each buffer
  S32 readsize;       // size of each read block

  U32 buf1;           // 0,1,2 (current buffer that we are reading into)
  S32 size1;          // holds the current amount of data read

  U32 buf2;           // 0,1,2 (the next buffer that we are reading into)
  S32 size2;          // next buffer loaded up to

  U32 buf3;           // 0,1,2 (the next buffer that we are reading into)
  S32 size3;          // next buffer loaded up to

  U32 datarate;       // datarate in bytes per second
  S32 filerate;       // original datarate of the file
  S32 filetype;       // file format type
  U32 fileflags;      // file format flags (signed or unsigned)
  S32 totallen;       // total length of the sound data

  S32 substart;       // subblock loop start
  S32 sublen;         // subblock loop len
  S32 subpadding;     // amount to pad the final block

  U32 blocksize;      // ADPCM block size
  S32 padding;        // padding to be done
  S32 padded;         // padding done

  S32 loadedsome;     // have we done any loads?

  U32 startpos;       // point that the sound data begins
  U32 totalread;      // total bytes read from the disk

  U32 loopsleft;      // how many loops are left

  U32 error;          // read error has occurred

  S32 preload;        // preload the file into the first buffer
  U32 preloadpos;     // position to use in preload
  S32 noback;         // no background processing
  S32 alldone;        // alldone
  S32 primeamount;    // amount to load after a seek
  S32 readatleast;    // forced amount to read on next service

  S32 playcontrol;    // control: 0=stopped, 1=started, |8=paused, |16=sample paused

  AILSTREAMCB callback;  // end of stream callback

  S32 user_data[8];   // Miscellaneous user data
  void FAR* next;     // pointer to next stream

#if defined(IS_WINDOWS) || defined(IS_MAC)
  S32 autostreaming;  // are we autostreaming this stream
#endif

#ifdef IS_WINDOWS
  S32 cb_IsWin32s;    // Is the callback win32s?
#endif

  S32 docallback;     // set when it time to poll for a callback

#ifdef IS_MAC
  IOParam  stream_param;
  S32      donext;
  S32      donext1;
  U32      fillup;
  U32      session;
  U32      tamt;
  U32      buf;
  S32*     size;
  S32*     done;
  S32      done1;
  S32      done2;
  S32      done3;
  Boolean  force_quit;
#endif

} MSTREAM_TYPE;


DXDEC HSTREAM AILCALL AIL_open_stream(HDIGDRIVER dig, char const FAR * filename, S32 stream_mem);

DXDEC void AILCALL AIL_close_stream(HSTREAM stream);

DXDEC S32 AILCALL AIL_service_stream(HSTREAM stream, S32 fillup);

DXDEC void AILCALL AIL_start_stream(HSTREAM stream);

DXDEC void AILCALL AIL_pause_stream(HSTREAM stream, S32 onoff);

DXDEC void AILCALL AIL_set_stream_volume(HSTREAM stream,S32 volume);

DXDEC void AILCALL AIL_set_stream_pan(HSTREAM stream,S32 pan);

DXDEC S32 AILCALL AIL_stream_volume(HSTREAM stream);

DXDEC S32 AILCALL AIL_stream_pan(HSTREAM stream);

DXDEC void AILCALL AIL_set_stream_playback_rate(HSTREAM stream, S32 rate);

DXDEC S32 AILCALL AIL_stream_playback_rate(HSTREAM stream);

DXDEC S32 AILCALL AIL_stream_loop_count(HSTREAM stream);

DXDEC void AILCALL AIL_set_stream_loop_count(HSTREAM stream, S32 count);

DXDEC void AILCALL AIL_set_stream_loop_block (HSTREAM S,
                                              S32     loop_start_offset,
                                              S32     loop_end_offset);

DXDEC S32 AILCALL AIL_stream_status(HSTREAM stream);

DXDEC void AILCALL AIL_set_stream_position(HSTREAM stream,S32 offset);

DXDEC S32 AILCALL AIL_stream_position(HSTREAM stream);

DXDEC void AILCALL AIL_stream_info(HSTREAM stream, S32 FAR* datarate, S32 FAR* sndtype, S32 FAR* length, S32 FAR* memory);

DXDEC AILSTREAMCB AILCALL AIL_register_stream_callback(HSTREAM stream, AILSTREAMCB callback);

DXDEC void AILCALL AIL_auto_service_stream(HSTREAM stream, S32 onoff);

DXDEC void     AILCALL AIL_set_stream_user_data   (HSTREAM S,
                                                     U32     index,
                                                     S32     value);

DXDEC S32      AILCALL AIL_stream_user_data       (HSTREAM S,
                                                     U32     index);

DXDEC  void     AILCALL AIL_set_stream_ms_position   (HSTREAM S,
                                                      S32        milliseconds);

DXDEC  void     AILCALL AIL_stream_ms_position     (HSTREAM    S, //)
                                                    S32 FAR *  total_milliseconds,
                                                    S32 FAR *  current_milliseconds);

DXDEC  void     AILCALL AIL_set_stream_reverb(HSTREAM S,
                                              F32     reverb_level,
                                              F32     reverb_reflect_time,
                                              F32     reverb_decay_time);

DXDEC  void    AILCALL AIL_stream_reverb     (HSTREAM S,
                                              F32 FAR *reverb_level,
                                              F32 FAR *reverb_reflect_time,
                                              F32 FAR *reverb_decay_time);

DXDEC  HPROVIDER    AILCALL AIL_set_stream_processor  (HSTREAM     S,
                                                       SAMPLESTAGE pipeline_stage,
                                                       HPROVIDER   provider);

#ifdef IS_MAC
typedef struct MSS_FILE
{
  S32 file_type; // 0 = char*, 1 = FSSpec*
  void const FAR* file;
} MSS_FILE;
#else
typedef char MSS_FILE;
#endif

typedef U32  (AILCALLBACK FAR*AIL_file_open_callback)  (MSS_FILE const FAR* Filename,
                                                        U32 FAR* FileHandle);

typedef void (AILCALLBACK FAR*AIL_file_close_callback) (U32 FileHandle);

#define AIL_FILE_SEEK_BEGIN   0
#define AIL_FILE_SEEK_CURRENT 1
#define AIL_FILE_SEEK_END     2

typedef S32  (AILCALLBACK FAR*AIL_file_seek_callback)  (U32 FileHandle,
                                                        S32 Offset,
                                                        U32 Type);

typedef U32  (AILCALLBACK FAR*AIL_file_read_callback)  (U32 FileHandle,
                                                        void FAR* Buffer,
                                                        U32 Bytes);

DXDEC  void  AILCALL AIL_set_file_callbacks  (AIL_file_open_callback opencb,
                                              AIL_file_close_callback closecb,
                                              AIL_file_seek_callback seekcb,
                                              AIL_file_read_callback readcb);

#ifdef IS_32

typedef void FAR* (AILCALLBACK FAR*AIL_file_async_read_callback) (U32 FileHandle,
                                                                  void FAR* Buffer,
                                                                  U32 Bytes);

typedef S32 (AILCALLBACK FAR*AIL_file_async_status_callback)  (void FAR* async,
                                                               S32 wait,
                                                               U32 FAR* BytesRead);

DXDEC  void  AILCALL AIL_set_file_async_callbacks (AIL_file_open_callback opencb,
                                                   AIL_file_close_callback closecb,
                                                   AIL_file_seek_callback seekcb,
                                                   AIL_file_async_read_callback areadcb,
                                                   AIL_file_async_status_callback statuscb);

#endif

//
// High-level DLS functions
//

typedef struct _DLSFILEID {
  S32 id;
  struct _DLSFILEID FAR* next;
} DLSFILEID;

typedef struct _DLSFILEID FAR* HDLSFILEID;

typedef struct _DLSDEVICE {
  void FAR* pGetPref;
  void FAR* pSetPref;
  void FAR* pMSSOpen;
  void FAR* pOpen;
  void FAR* pClose;
  void FAR* pLoadFile;
  void FAR* pLoadMem;
  void FAR* pUnloadFile;
  void FAR* pUnloadAll;
  void FAR* pGetInfo;
  void FAR* pCompact;
  void FAR* pSetAttr;
  S32 DLSHandle;
  U32 format;
  U32 buffer_size;
  void FAR* buffer[2];
  HSAMPLE sample;
  HMDIDRIVER mdi;
  HDIGDRIVER dig;
  HDLSFILEID first;
#ifdef IS_WINDOWS
  HMODULE lib;
#else
  #ifdef IS_DOS
  char FAR* DOSname;
  #endif
#endif
} DLSDEVICE;

typedef struct _DLSDEVICE FAR* HDLSDEVICE;

typedef struct _AILDLSINFO {
  char Description[128];
  S32 MaxDLSMemory;
  S32 CurrentDLSMemory;
  S32 LargestSize;
  S32 GMAvailable;
  S32 GMBankSize;
} AILDLSINFO;

#ifdef IS_DOS

typedef struct _AILDOSDLS {
  char FAR* description;
  void FAR* pDLSOpen;
  void FAR* pMSSOpen;
  void FAR* pOpen;
  void FAR* pClose;
  void FAR* pLoadFile;
  void FAR* pLoadMem;
  void FAR* pUnloadFile;
  void FAR* pUnloadAll;
  void FAR* pGetInfo;
  void FAR* pCompact;
  void FAR* pSetAttr;
} AILDOSDLS;

#endif


DXDEC  HDLSDEVICE AILCALL AIL_DLS_open(HMDIDRIVER mdi, HDIGDRIVER dig,
#if defined(IS_WINDOWS) || defined(IS_MAC)
                                          char const FAR * libname,
#else
                                          AILDOSDLS const FAR * dosdls,
#endif
                                          U32 flags, U32 rate, S32 bits, S32 channels);

//
// Parameters for the dwFlag used in DLSClose() and flags in AIL_DLS_close
//

#define RETAIN_DLS_COLLECTION   0x00000001
#define RETURN_TO_BOOTUP_STATE  0x00000002
#define RETURN_TO_GM_ONLY_STATE 0x00000004
#define DLS_COMPACT_MEMORY      0x00000008

DXDEC  void   AILCALL AIL_DLS_close(HDLSDEVICE dls, U32 flags);

DXDEC  HDLSFILEID AILCALL AIL_DLS_load_file(HDLSDEVICE dls, char const FAR* filename, U32 flags);

DXDEC  HDLSFILEID AILCALL AIL_DLS_load_memory(HDLSDEVICE dls, void const FAR* memfile, U32 flags);

//
// other parameters for AIL_DLS_unload
//

#define AIL_DLS_UNLOAD_MINE 0
#define AIL_DLS_UNLOAD_ALL  ((HDLSFILEID)(U32)(S32)-1)

DXDEC  void   AILCALL AIL_DLS_unload(HDLSDEVICE dls, HDLSFILEID dlsid);

DXDEC  void   AILCALL AIL_DLS_compact(HDLSDEVICE dls);

DXDEC  void   AILCALL AIL_DLS_get_info(HDLSDEVICE dls, AILDLSINFO FAR* info, S32 FAR* PercentCPU);

DXDEC  void   AILCALL AIL_DLS_set_reverb(HDLSDEVICE dls,
                                         F32     reverb_level,
                                         F32     reverb_reflect_time,
                                         F32     reverb_decay_time);

DXDEC  void   AILCALL AIL_DLS_get_reverb(HDLSDEVICE dls,
                                         F32 FAR*    reverb_level,
                                         F32 FAR*    reverb_reflect_time,
                                         F32 FAR*    reverb_decay_time);

DXDEC  HPROVIDER    AILCALL AIL_set_DLS_processor     (HDLSDEVICE  dev,
                                                       SAMPLESTAGE pipeline_stage,
                                                       HPROVIDER   provider);


//
// Quick-integration service functions and data types
//

typedef struct
{
   U32 const FAR *data;
   S32  size;
   S32  type;
   void FAR *handle;
   S32  status;
   void FAR* next;
   S32  speed;
   S32  volume;
   S32  extravol;
   F32  rlevel;
   F32  rrtime;
   F32  rdtime;
   HDLSFILEID dlsid;
   void FAR* dlsmem;
   void FAR* dlsmemunc;
   S32  milliseconds;
   S32  length;
   S32  userdata;
}
AUDIO_TYPE;


#define QSTAT_DONE          1       // Data has finished playing
#define QSTAT_LOADED        2       // Data has been loaded, but not yet played
#define QSTAT_PLAYING       3       // Data is currently playing

typedef AUDIO_TYPE FAR * HAUDIO;        // Generic handle to any audio data type

#define AIL_QUICK_USE_WAVEOUT             2
#define AIL_QUICK_MIDI_AND_DLS            2
#define AIL_QUICK_DLS_ONLY                3
#define AIL_QUICK_MIDI_AND_VORTEX_DLS     4
#define AIL_QUICK_MIDI_AND_SONICVIBES_DLS 5

DXDEC S32     AILCALL
#if defined(IS_WINDOWS) || defined(IS_MAC)
                       AIL_quick_startup           (
#else
                       AIL_quick_startup_with_start(void*       startup,
#endif
                                                    S32         use_digital,
                                                    S32         use_MIDI,
                                                    U32         output_rate,
                                                    S32         output_bits,
                                                    S32         output_channels);

DXDEC void    AILCALL AIL_quick_shutdown            (void);

DXDEC void    AILCALL AIL_quick_handles             (HDIGDRIVER FAR* pdig,
                                                     HMDIDRIVER FAR* pmdi,
                                                     HDLSDEVICE FAR* pdls );

DXDEC HAUDIO  AILCALL AIL_quick_load                (char const   FAR *filename);

#ifdef IS_MAC
DXDEC HAUDIO  AILCALL AIL_quick_fss_load            (FSSpec const   FAR *filename);
#endif

DXDEC HAUDIO  AILCALL AIL_quick_load_mem            (void const   FAR *mem,
                                                    U32    size);

DXDEC HAUDIO  AILCALL AIL_quick_copy                (HAUDIO      audio);

DXDEC void    AILCALL AIL_quick_unload              (HAUDIO      audio);

DXDEC S32     AILCALL AIL_quick_play                (HAUDIO      audio,
                                                    U32         loop_count);

DXDEC void    AILCALL AIL_quick_halt                (HAUDIO      audio);

DXDEC S32     AILCALL AIL_quick_status              (HAUDIO      audio);

DXDEC HAUDIO  AILCALL AIL_quick_load_and_play       (char const   FAR *filename,
                                                    U32         loop_count,
                                                    S32         wait_request);

#ifdef IS_MAC
DXDEC HAUDIO  AILCALL AIL_quick_fss_load_and_play  (FSSpec const   FAR *filename,
                                                    U32         loop_count,
                                                    S32         wait_request);
#endif

DXDEC void   AILCALL AIL_quick_set_speed (HAUDIO audio, S32 speed);

DXDEC void   AILCALL AIL_quick_set_volume (HAUDIO audio, S32 volume, S32 extravol);

DXDEC void   AILCALL AIL_quick_set_reverb (HAUDIO audio,
                                           F32     reverb_level,
                                           F32     reverb_reflect_time,
                                           F32     reverb_decay_time);

DXDEC void   AILCALL AIL_quick_set_ms_position(HAUDIO audio,S32 milliseconds);

DXDEC S32    AILCALL AIL_quick_ms_position(HAUDIO audio);

DXDEC S32    AILCALL AIL_quick_ms_length(HAUDIO audio);


#define AIL_QUICK_XMIDI_TYPE        1
#define AIL_QUICK_DIGITAL_TYPE      2
#define AIL_QUICK_DLS_XMIDI_TYPE    3
#define AIL_QUICK_MPEG_DIGITAL_TYPE 4

DXDEC S32    AILCALL AIL_quick_type(HAUDIO audio);

//
// used for AIL_process
//

typedef struct _AILMIXINFO {
  AILSOUNDINFO Info;
  ADPCMDATA mss_adpcm;
  U32 src_fract;
  S32 left_val;
  S32 right_val;
} AILMIXINFO;



DXDEC S32 AILCALL AIL_WAV_info(void const FAR* data, AILSOUNDINFO FAR* info);

DXDEC S32 AILCALL AIL_size_processed_digital_audio(
                                 U32             dest_rate,
                                 U32             dest_format,
                                 S32             num_srcs,
                                 AILMIXINFO const FAR* src);

DXDEC S32 AILCALL AIL_process_digital_audio(
                                 void FAR       *dest_buffer,
                                 S32             dest_buffer_size,
                                 U32             dest_rate,
                                 U32             dest_format,
                                 S32             num_srcs,
                                 AILMIXINFO FAR* src);

#define AIL_LENGTHY_INIT           0
#define AIL_LENGTHY_SET_PREFERENCE 1
#define AIL_LENGTHY_UPDATE         2
#define AIL_LENGTHY_DONE           3

typedef S32 (AILCALLBACK FAR* AILLENGTHYCB)(U32 state,U32 user);

typedef S32 (AILCALLBACK FAR* AILCODECSETPREF)(char const FAR* preference,U32 value);

DXDEC S32 AILCALL AIL_compress_ASI(AILSOUNDINFO const FAR * info, //)
                                   char const FAR* filename_ext,
                                   void FAR* FAR* outdata,
                                   U32 FAR* outsize,
                                   AILLENGTHYCB callback);

DXDEC S32 AILCALL AIL_decompress_ASI(void const FAR* indata, //)
                                     U32 insize,
                                     char const FAR* filename_ext,
                                     void FAR* FAR* wav,
                                     U32 FAR* wavsize,
                                     AILLENGTHYCB callback);

DXDEC S32 AILCALL AIL_compress_ADPCM(AILSOUNDINFO const FAR * info,
                                     void FAR* FAR* outdata, U32 FAR* outsize);

DXDEC S32 AILCALL AIL_decompress_ADPCM(AILSOUNDINFO const FAR * info,
                                       void FAR* FAR* outdata, U32 FAR* outsize);

DXDEC S32 AILCALL AIL_compress_DLS(void const FAR* dls,
                                   char const FAR* compression_extension,
                                   void FAR* FAR* mls, U32 FAR* mlssize,
                                   AILLENGTHYCB callback);

DXDEC S32 AILCALL AIL_merge_DLS_with_XMI(void const FAR* xmi, void const FAR* dls,
                                         void FAR* FAR* mss, U32 FAR* msssize);

DXDEC  S32 AILCALL AIL_extract_DLS( void const FAR *source_image, //)
                                    U32             source_size,
                                    void FAR * FAR *XMI_output_data,
                                    U32  FAR       *XMI_output_size,
                                    void FAR * FAR *DLS_output_data,
                                    U32  FAR       *DLS_output_size,
                                    AILLENGTHYCB   callback);

#define AILFILTERDLS_USINGLIST 1

DXDEC S32 AILCALL AIL_filter_DLS_with_XMI(void const FAR* xmi, void const FAR* dls,
                                         void FAR* FAR* dlsout, U32 FAR* dlssize,
                                         S32  flags, AILLENGTHYCB callback);

#define AILMIDITOXMI_USINGLIST 1
#define AILMIDITOXMI_TOLERANT  2

DXDEC  S32 AILCALL AIL_MIDI_to_XMI       (void const FAR*  MIDI,
                                         U32        MIDI_size,
                                         void FAR*  FAR*XMIDI,
                                         U32  FAR*  XMIDI_size,
                                         S32        flags);

#define AILMIDILIST_ROLANDSYSEX 1
#define AILMIDILIST_ROLANDUN    2
#define AILMIDILIST_ROLANDAB    4

DXDEC  S32          AILCALL AIL_list_MIDI         (void const FAR* MIDI,
                                                  U32       MIDI_size,
                                                  char FAR* FAR* lst,
                                                  U32  FAR* lst_size,
                                                  S32       flags);
#define AILDLSLIST_ARTICULATION 1
#define AILDLSLIST_DUMP_WAVS    2

DXDEC  S32          AILCALL AIL_list_DLS          (void const FAR* DLS,
                                                   char FAR* FAR* lst,
                                                   U32  FAR* lst_size,
                                                   S32       flags,
                                                   C8   FAR* title);

#define AILFILETYPE_UNKNOWN     0
#define AILFILETYPE_PCM_WAV     1
#define AILFILETYPE_ADPCM_WAV   2
#define AILFILETYPE_OTHER_WAV   3
#define AILFILETYPE_VOC         4
#define AILFILETYPE_MIDI        5
#define AILFILETYPE_XMIDI       6
#define AILFILETYPE_XMIDI_DLS   7
#define AILFILETYPE_XMIDI_MLS   8
#define AILFILETYPE_DLS         9
#define AILFILETYPE_MLS        10
#define AILFILETYPE_MPEG_L1_AUDIO 11
#define AILFILETYPE_MPEG_L2_AUDIO 12
#define AILFILETYPE_MPEG_L3_AUDIO 13
#define AILFILETYPE_OTHER_ASI_WAV 14


DXDEC S32 AILCALL AIL_file_type(void const FAR* data, U32 size);

DXDEC S32 AILCALL AIL_find_DLS       (void const FAR*      data, U32 size,
                                      void FAR* FAR* xmi, U32 FAR* xmisize,
                                      void FAR* FAR* dls, U32 FAR* dlssize);

#if defined(IS_WIN32) || defined(IS_MAC)

//
// Auxiliary 2D interface calls
//

DXDEC HDIGDRIVER AILCALL AIL_primary_digital_driver  (HDIGDRIVER new_primary);

//
// Filter result codes
//

typedef S32 FLTRESULT;

#define FLT_NOERR                   0   // Success -- no error
#define FLT_NOT_ENABLED             1   // FLT not enabled
#define FLT_ALREADY_STARTED         2   // FLT already started
#define FLT_INVALID_PARAM           3   // Invalid parameters used
#define FLT_INTERNAL_ERR            4   // Internal error in FLT driver
#define FLT_OUT_OF_MEM              5   // Out of system RAM
#define FLT_ERR_NOT_IMPLEMENTED     6   // Feature not implemented
#define FLT_NOT_FOUND               7   // FLT supported device not found
#define FLT_NOT_INIT                8   // FLT not initialized
#define FLT_CLOSE_ERR               9   // FLT not closed correctly

//############################################################################
//##                                                                        ##
//## Interface "MSS pipeline filter"                                        ##
//##                                                                        ##
//############################################################################

typedef FLTRESULT (AILCALL FAR *FLT_STARTUP)(void);

typedef FLTRESULT (AILCALL FAR *FLT_SHUTDOWN)(void);

typedef C8 FAR *  (AILCALL FAR *FLT_ERROR)(void);

typedef S32       (AILCALL FAR *FLT_SET_PROVIDER_PREFERENCE)(HATTRIB preference,
                                                             void const FAR*   value);

typedef HDRIVERSTATE (AILCALL FAR *FLT_OPEN_DRIVER) (HDIGDRIVER dig,
                                                     S32 FAR   *build_buffer,
                                                     S32        build_buffer_size);

typedef FLTRESULT    (AILCALL FAR *FLT_CLOSE_DRIVER) (HDRIVERSTATE state);

typedef void         (AILCALL FAR *FLT_PREMIX_PROCESS) (HDRIVERSTATE driver
#ifdef IS_MAC
                                                       ,U32 buffer_size
#endif
);

typedef void         (AILCALL FAR *FLT_POSTMIX_PROCESS) (HDRIVERSTATE driver
#ifdef IS_MAC
                                                       ,U32 buffer_size
#endif
);

//############################################################################
//##                                                                        ##
//## Interface "Pipeline filter sample services"                            ##
//##                                                                        ##
//############################################################################

typedef HSAMPLESTATE (AILCALL FAR * FLTSMP_OPEN_SAMPLE) (HDRIVERSTATE driver,
                                                         HSAMPLE      S);

typedef FLTRESULT    (AILCALL FAR * FLTSMP_CLOSE_SAMPLE) (HSAMPLESTATE state);

typedef S32          (AILCALL FAR * FLTSMP_SAMPLE_PROCESS) (HSAMPLESTATE    state,
                                                            void const FAR * FAR *orig_src,
                                                            U32  FAR *      orig_src_fract,
                                                            void FAR *      orig_src_end,
                                                            S32  FAR * FAR *build_dest,
                                                            void FAR *      build_dest_end,
                                                            S32  FAR *      left_val,
                                                            S32  FAR *      right_val,
                                                            S32             playback_ratio,
                                                            S32             left_scale,
                                                            S32             right_scale,
                                                            S32             base_scale,
                                                            MIXSTAGE FAR *  mixer_provider,
                                                            U32             mixer_operation);

typedef S32          (AILCALL FAR * FLTSMP_SAMPLE_ATTRIBUTE) (HSAMPLESTATE state,
                                                              HATTRIB      attribute);

typedef S32          (AILCALL FAR * FLTSMP_SET_SAMPLE_PREFERENCE) (HSAMPLESTATE state,
                                                                   HATTRIB      preference,
                                                                   void const FAR*    value);

//
// Pipeline filter calls
//

DXDEC S32        AILCALL AIL_enumerate_filters  (HPROENUM  FAR *next,
                                                 HPROVIDER FAR *dest,
                                                 C8  FAR * FAR *name);

DXDEC HDRIVERSTATE
                 AILCALL AIL_open_filter        (HPROVIDER  lib,
                                                 HDIGDRIVER dig);

DXDEC void       AILCALL AIL_close_filter       (HDRIVERSTATE filter);

DXDEC S32        AILCALL AIL_enumerate_filter_attributes
                                                (HPROVIDER                  lib,
                                                 HINTENUM FAR *             next,
                                                 RIB_INTERFACE_ENTRY FAR *  dest);

DXDEC void       AILCALL AIL_filter_attribute   (HPROVIDER  lib,
                                                 C8 const FAR*   name,
                                                 void FAR * val);

DXDEC void       AILCALL AIL_set_filter_preference
                                                (HPROVIDER  lib,
                                                 C8 const FAR*   name,
                                                 void const FAR* val);

DXDEC  S32      AILCALL AIL_enumerate_filter_sample_attributes
                                                (HPROVIDER                 lib,
                                                 HINTENUM FAR *            next,
                                                 RIB_INTERFACE_ENTRY FAR * dest);

DXDEC  void     AILCALL AIL_filter_sample_attribute
                                                (HSAMPLE    S,
                                                 C8 const FAR*   name,
                                                 void FAR * val);

DXDEC  void     AILCALL AIL_filter_stream_attribute
                                                (HSTREAM    S,
                                                 C8 const FAR*   name,
                                                 void FAR* val);

DXDEC  void     AILCALL AIL_filter_DLS_attribute
                                                (HDLSDEVICE dls,
                                                 C8 const FAR*   name,
                                                 void FAR * val);

DXDEC  void     AILCALL AIL_set_filter_sample_preference
                                                (HSAMPLE    S,
                                                 C8 const FAR *   name,
                                                 void const FAR * val);

DXDEC  void     AILCALL AIL_set_filter_stream_preference
                                                (HSTREAM    S,
                                                 C8 const FAR *   name,
                                                 void const FAR * val);

DXDEC  void     AILCALL AIL_set_filter_DLS_preference
                                                (HDLSDEVICE dls,
                                                 C8 const FAR *   name,
                                                 void const FAR * val);

typedef struct _FLTPROVIDER
{
   PROVIDER_QUERY_ATTRIBUTE        PROVIDER_query_attribute;

   FLT_STARTUP                     startup;
   FLT_ERROR                       error;
   FLT_SHUTDOWN                    shutdown;
   FLT_SET_PROVIDER_PREFERENCE     set_provider_preference;
   FLT_OPEN_DRIVER                 open_driver;
   FLT_CLOSE_DRIVER                close_driver;
   FLT_PREMIX_PROCESS              premix_process;
   FLT_POSTMIX_PROCESS             postmix_process;

   FLTSMP_OPEN_SAMPLE              open_sample;
   FLTSMP_CLOSE_SAMPLE             close_sample;
   FLTSMP_SAMPLE_PROCESS           sample_process;
   FLTSMP_SAMPLE_ATTRIBUTE         sample_attribute;
   FLTSMP_SET_SAMPLE_PREFERENCE    set_sample_preference;

   HDIGDRIVER   dig;
   HPROVIDER    provider;
   HDRIVERSTATE driver_state;

   struct _FLTPROVIDER FAR *next;
}
FLTPROVIDER;

//
// 3D provider calls
//

DXDEC S32        AILCALL AIL_enumerate_3D_providers  (HPROENUM  FAR *next,
                                                      HPROVIDER FAR *dest,
                                                      C8  FAR * FAR *name);

DXDEC M3DRESULT  AILCALL AIL_open_3D_provider        (HPROVIDER lib);

DXDEC void       AILCALL AIL_close_3D_provider       (HPROVIDER lib);

DXDEC S32        AILCALL AIL_enumerate_3D_provider_attributes
                                                     (HPROVIDER                  lib,
                                                      HINTENUM FAR *             next,
                                                      RIB_INTERFACE_ENTRY FAR *  dest);

DXDEC void       AILCALL AIL_3D_provider_attribute   (HPROVIDER   lib,
                                                      C8 const FAR*    name,
                                                      void FAR *  val);

DXDEC void       AILCALL AIL_set_3D_provider_preference(HPROVIDER   lib,
                                                        C8 const FAR*    name,
                                                        void const FAR*  val);

struct H3D
{
   H3DPOBJECT actual;
   HPROVIDER  owner;
   S32        user_data[8];
};

typedef struct _M3DPROVIDER
{
   PROVIDER_QUERY_ATTRIBUTE        PROVIDER_query_attribute;
   M3D_STARTUP                     startup;
   M3D_ERROR                       error;
   M3D_SHUTDOWN                    shutdown;
   M3D_SET_PROVIDER_PREFERENCE     set_provider_preference;
   M3D_ACTIVATE                    activate;
   M3D_ALLOCATE_3D_SAMPLE_HANDLE   allocate_3D_sample_handle;
   M3D_RELEASE_3D_SAMPLE_HANDLE    release_3D_sample_handle;
   M3D_START_3D_SAMPLE             start_3D_sample;
   M3D_STOP_3D_SAMPLE              stop_3D_sample;
   M3D_RESUME_3D_SAMPLE            resume_3D_sample;
   M3D_END_3D_SAMPLE               end_3D_sample;
   M3D_SET_3D_SAMPLE_DATA          set_3D_sample_data;
   M3D_SET_3D_SAMPLE_VOLUME        set_3D_sample_volume;
   M3D_SET_3D_SAMPLE_PLAYBACK_RATE set_3D_sample_playback_rate;
   M3D_SET_3D_SAMPLE_OFFSET        set_3D_sample_offset;
   M3D_SET_3D_SAMPLE_LOOP_COUNT    set_3D_sample_loop_count;
   M3D_SET_3D_SAMPLE_LOOP_BLOCK    set_3D_sample_loop_block;
   M3D_3D_SAMPLE_STATUS            sample_status;
   M3D_3D_SAMPLE_VOLUME            sample_volume;
   M3D_3D_SAMPLE_PLAYBACK_RATE     sample_playback_rate;
   M3D_3D_SAMPLE_OFFSET            sample_offset;
   M3D_3D_SAMPLE_LENGTH            sample_length;
   M3D_3D_SAMPLE_LOOP_COUNT        sample_loop_count;
   M3D_SET_3D_SAMPLE_DISTANCES     set_3D_sample_distances;
   M3D_3D_SAMPLE_DISTANCES         sample_distances;
   M3D_ACTIVE_3D_SAMPLE_COUNT      active_3D_sample_count;
   M3D_3D_OPEN_LISTENER            open_listener;
   M3D_3D_CLOSE_LISTENER           close_listener;
   M3D_3D_OPEN_OBJECT              open_object;
   M3D_3D_CLOSE_OBJECT             close_object;
   M3D_SET_3D_POSITION             set_3D_position;
   M3D_SET_3D_VELOCITY             set_3D_velocity;
   M3D_SET_3D_VELOCITY_VECTOR      set_3D_velocity_vector;
   M3D_SET_3D_ORIENTATION          set_3D_orientation;
   M3D_3D_POSITION                 position;
   M3D_3D_VELOCITY                 velocity;
   M3D_3D_ORIENTATION              orientation;
   M3D_3D_UPDATE_POSITION          update_position;
   M3D_3D_AUTO_UPDATE_POSITION     auto_update_position;
   M3D_3D_SAMPLE_ATTRIBUTE         sample_query_attribute;
   M3D_3D_SET_SAMPLE_PREFERENCE    set_sample_preference;
   M3D_3D_ROOM_TYPE                room_type;
   M3D_SET_3D_ROOM_TYPE            set_3D_room_type;
   M3D_3D_SPEAKER_TYPE             speaker_type;
   M3D_SET_3D_SPEAKER_TYPE         set_3D_speaker_type;
   M3D_SET_3D_SAMPLE_OBSTRUCTION   set_3D_sample_obstruction;
   M3D_SET_3D_SAMPLE_OCCLUSION     set_3D_sample_occlusion;
   M3D_SET_3D_SAMPLE_CONE          set_3D_sample_cone;
   M3D_SET_3D_SAMPLE_EFFECTS_LEVEL set_3D_sample_effects_level;
   M3D_3D_SAMPLE_OBSTRUCTION       sample_obstruction;
   M3D_3D_SAMPLE_OCCLUSION         sample_occlusion;
   M3D_3D_SAMPLE_CONE              sample_cone;
   M3D_3D_SAMPLE_EFFECTS_LEVEL     sample_effects_level;
   M3D_SET_3D_EOS                  set_3D_EOS;
} M3DPROVIDER;

//
// Sample calls
//

DXDEC H3DSAMPLE  AILCALL AIL_allocate_3D_sample_handle
                                                     (HPROVIDER lib);


DXDEC void       AILCALL AIL_release_3D_sample_handle
                                                     (H3DSAMPLE S);


DXDEC void       AILCALL AIL_start_3D_sample         (H3DSAMPLE S);


DXDEC void       AILCALL AIL_stop_3D_sample          (H3DSAMPLE S);


DXDEC void       AILCALL AIL_resume_3D_sample        (H3DSAMPLE S);

DXDEC void       AILCALL AIL_end_3D_sample           (H3DSAMPLE S);

DXDEC S32        AILCALL AIL_set_3D_sample_file      (H3DSAMPLE S,
                                                      void const FAR*file_image);

DXDEC S32        AILCALL AIL_set_3D_sample_info      (H3DSAMPLE         S,
                                                      AILSOUNDINFO const FAR*info);

DXDEC void       AILCALL AIL_set_3D_sample_volume    (H3DSAMPLE S,
                                                      S32       volume);

DXDEC void       AILCALL AIL_set_3D_sample_offset    (H3DSAMPLE S,
                                                      U32       offset);

DXDEC void       AILCALL AIL_set_3D_sample_playback_rate
                                                     (H3DSAMPLE S,
                                                      S32       playback_rate);

DXDEC void       AILCALL AIL_set_3D_sample_loop_count(H3DSAMPLE S,
                                                      U32       loops);

DXDEC void       AILCALL AIL_set_3D_sample_loop_block(H3DSAMPLE S,
                                                      S32       loop_start_offset,
                                                      S32       loop_end_offset);

DXDEC U32        AILCALL AIL_3D_sample_status        (H3DSAMPLE S);

DXDEC S32        AILCALL AIL_3D_sample_volume        (H3DSAMPLE S);

DXDEC U32        AILCALL AIL_3D_sample_offset        (H3DSAMPLE S);

DXDEC S32        AILCALL AIL_3D_sample_playback_rate (H3DSAMPLE S);

DXDEC U32        AILCALL AIL_3D_sample_length        (H3DSAMPLE S);

DXDEC U32        AILCALL AIL_3D_sample_loop_count    (H3DSAMPLE S);


DXDEC  S32      AILCALL AIL_3D_room_type             (HPROVIDER lib);

DXDEC  void     AILCALL AIL_set_3D_room_type         (HPROVIDER lib,
                                                      S32       room_type);

#define AIL_3D_2_SPEAKER  0
#define AIL_3D_HEADPHONE  1
#define AIL_3D_SURROUND   2
#define AIL_3D_4_SPEAKER  3


DXDEC  S32      AILCALL AIL_3D_speaker_type          (HPROVIDER lib);

DXDEC  void     AILCALL AIL_set_3D_speaker_type      (HPROVIDER lib,
                                                      S32       speaker_type);


//
// Changed the definition of distances to only be max and min, vs. front
//   min/max and back min/max.  Only RSX supported the concept of different
//   front and distances, so we changed the API to make it more orthogonal
//   to most of the 3D providers. Sorry in advance.
//

DXDEC void       AILCALL AIL_set_3D_sample_distances (H3DSAMPLE S,
                                                      F32       max_dist,
                                                      F32       min_dist);


DXDEC void       AILCALL AIL_3D_sample_distances     (H3DSAMPLE S,
                                                      F32 FAR * max_dist,
                                                      F32 FAR * min_dist);

DXDEC  S32      AILCALL AIL_active_3D_sample_count   (HPROVIDER lib);

DXDEC  S32      AILCALL AIL_enumerate_3D_sample_attributes
                                                     (HPROVIDER                  lib,
                                                      HINTENUM FAR *             next,
                                                      RIB_INTERFACE_ENTRY FAR *  dest);

DXDEC  void     AILCALL AIL_3D_sample_attribute      (H3DSAMPLE   samp,
                                                      C8 const FAR*    name,
                                                      void FAR *  val);


DXDEC  void     AILCALL AIL_set_3D_sample_preference (H3DSAMPLE   samp,
                                                      C8 const FAR*    name,
                                                      void const FAR*  val);

DXDEC void       AILCALL AIL_set_3D_sample_obstruction (H3DSAMPLE S,
                                                        F32       obstruction);

DXDEC void       AILCALL AIL_set_3D_sample_occlusion   (H3DSAMPLE S,
                                                        F32       occlusion);

DXDEC void       AILCALL AIL_set_3D_sample_cone        (H3DSAMPLE S,
                                                        F32       inner_angle,
                                                        F32       outer_angle,
                                                        S32       outer_volume);

DXDEC void       AILCALL AIL_set_3D_sample_effects_level 
                                                       (H3DSAMPLE S,
                                                        F32       effects_level);

DXDEC F32        AILCALL AIL_3D_sample_obstruction     (H3DSAMPLE S);

DXDEC F32        AILCALL AIL_3D_sample_occlusion       (H3DSAMPLE S);

DXDEC void       AILCALL AIL_3D_sample_cone            (H3DSAMPLE S,
                                                        F32 FAR*  inner_angle,
                                                        F32 FAR*  outer_angle,
                                                        S32 FAR*  outer_volume);

DXDEC F32        AILCALL AIL_3D_sample_effects_level   (H3DSAMPLE S);


DXDEC AIL3DSAMPLECB AILCALL AIL_register_3D_EOS_callback
                                                       (H3DSAMPLE S,
                                                        AIL3DSAMPLECB EOS);


//
// Positioning-object allocation calls
//

DXDEC H3DPOBJECT AILCALL AIL_open_3D_listener        (HPROVIDER lib);

DXDEC void       AILCALL AIL_close_3D_listener       (H3DPOBJECT listener);

DXDEC H3DPOBJECT AILCALL AIL_open_3D_object          (HPROVIDER lib);

DXDEC void       AILCALL AIL_close_3D_object         (H3DPOBJECT obj);

//
// 3D object calls
//

DXDEC void       AILCALL AIL_set_3D_position         (H3DPOBJECT obj,
                                                      F32     X,
                                                      F32     Y,
                                                      F32     Z);

DXDEC void       AILCALL AIL_set_3D_velocity         (H3DPOBJECT obj,
                                                      F32     dX_per_ms,
                                                      F32     dY_per_ms,
                                                      F32     dZ_per_ms,
                                                      F32     magnitude);

DXDEC void       AILCALL AIL_set_3D_velocity_vector  (H3DPOBJECT obj,
                                                      F32     dX_per_ms,
                                                      F32     dY_per_ms,
                                                      F32     dZ_per_ms);

DXDEC void       AILCALL AIL_set_3D_orientation      (H3DPOBJECT obj,
                                                      F32     X_face,
                                                      F32     Y_face,
                                                      F32     Z_face,
                                                      F32     X_up,
                                                      F32     Y_up,
                                                      F32     Z_up);

DXDEC void       AILCALL AIL_3D_position             (H3DPOBJECT  obj,
                                                      F32 FAR *X,
                                                      F32 FAR *Y,
                                                      F32 FAR *Z);

DXDEC void       AILCALL AIL_3D_velocity             (H3DPOBJECT  obj,
                                                      F32 FAR *dX_per_ms,
                                                      F32 FAR *dY_per_ms,
                                                      F32 FAR *dZ_per_ms);

DXDEC void       AILCALL AIL_3D_orientation          (H3DPOBJECT  obj,
                                                      F32 FAR *X_face,
                                                      F32 FAR *Y_face,
                                                      F32 FAR *Z_face,
                                                      F32 FAR *X_up,
                                                      F32 FAR *Y_up,
                                                      F32 FAR *Z_up);

DXDEC void       AILCALL AIL_update_3D_position      (H3DPOBJECT obj,
                                                      F32     dt_milliseconds);

DXDEC void       AILCALL AIL_auto_update_3D_position (H3DPOBJECT obj,
                                                      S32        enable);

DXDEC  void     AILCALL AIL_set_3D_user_data         (H3DPOBJECT obj,
                                                      U32        index,
                                                      S32        value);

DXDEC  S32      AILCALL AIL_3D_user_data             (H3DPOBJECT obj,
                                                      U32        index);

// Obsolete 3D function names:
#define AIL_set_3D_object_user_data AIL_set_3D_user_data
#define AIL_3D_object_user_data AIL_3D_user_data
#define AIL_3D_open_listener AIL_open_3D_listener
#define AIL_3D_close_listener AIL_close_3D_listener
#define AIL_3D_open_object AIL_open_3D_object
#define AIL_3D_close_object AIL_close_3D_object

//
// RAD room types - currently the same as EAX
//

enum
{
    ENVIRONMENT_GENERIC,                // factory default
    ENVIRONMENT_PADDEDCELL,
    ENVIRONMENT_ROOM,                   // standard environments
    ENVIRONMENT_BATHROOM,
    ENVIRONMENT_LIVINGROOM,
    ENVIRONMENT_STONEROOM,
    ENVIRONMENT_AUDITORIUM,
    ENVIRONMENT_CONCERTHALL,
    ENVIRONMENT_CAVE,
    ENVIRONMENT_ARENA,
    ENVIRONMENT_HANGAR,
    ENVIRONMENT_CARPETEDHALLWAY,
    ENVIRONMENT_HALLWAY,
    ENVIRONMENT_STONECORRIDOR,
    ENVIRONMENT_ALLEY,
    ENVIRONMENT_FOREST,
    ENVIRONMENT_CITY,
    ENVIRONMENT_MOUNTAINS,
    ENVIRONMENT_QUARRY,
    ENVIRONMENT_PLAIN,
    ENVIRONMENT_PARKINGLOT,
    ENVIRONMENT_SEWERPIPE,
    ENVIRONMENT_UNDERWATER,
    ENVIRONMENT_DRUGGED,
    ENVIRONMENT_DIZZY,
    ENVIRONMENT_PSYCHOTIC,

    ENVIRONMENT_COUNT           // total number of environments
};

//
// enumerated values for EAX
//

#ifndef EAX_H_INCLUDED

enum
{
    EAX_ENVIRONMENT_GENERIC,                // factory default
    EAX_ENVIRONMENT_PADDEDCELL,
    EAX_ENVIRONMENT_ROOM,              // standard environments
    EAX_ENVIRONMENT_BATHROOM,
    EAX_ENVIRONMENT_LIVINGROOM,
    EAX_ENVIRONMENT_STONEROOM,
    EAX_ENVIRONMENT_AUDITORIUM,
    EAX_ENVIRONMENT_CONCERTHALL,
    EAX_ENVIRONMENT_CAVE,
    EAX_ENVIRONMENT_ARENA,
    EAX_ENVIRONMENT_HANGAR,
    EAX_ENVIRONMENT_CARPETEDHALLWAY,
    EAX_ENVIRONMENT_HALLWAY,
    EAX_ENVIRONMENT_STONECORRIDOR,
    EAX_ENVIRONMENT_ALLEY,
    EAX_ENVIRONMENT_FOREST,
    EAX_ENVIRONMENT_CITY,
    EAX_ENVIRONMENT_MOUNTAINS,
    EAX_ENVIRONMENT_QUARRY,
    EAX_ENVIRONMENT_PLAIN,
    EAX_ENVIRONMENT_PARKINGLOT,
    EAX_ENVIRONMENT_SEWERPIPE,
    EAX_ENVIRONMENT_UNDERWATER,
    EAX_ENVIRONMENT_DRUGGED,
    EAX_ENVIRONMENT_DIZZY,
    EAX_ENVIRONMENT_PSYCHOTIC,

    EAX_ENVIRONMENT_COUNT           // total number of environments
};

#define EAX_REVERBMIX_USEDISTANCE (-1.0F)

#endif

#else

typedef struct _FLTPROVIDER
{
  U32 junk;
} FLTPROVIDER;

#endif

#ifdef __cplusplus
}
#endif


#if defined(_PUSHPOP_SUPPORTED) || PRAGMA_STRUCT_PACKPUSH
  #pragma pack(pop)
#else
  #pragma pack()
#endif


#endif
