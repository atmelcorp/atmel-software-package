

#define OVERRIDE_LAYOUT   0x010000
#define OVERRIDE_BUFSIZE  0x020000
#define OVERRIDE_PAGESIZE 0x040000

#define LAYOUT_OVERRIDE_BUFFER ((char*)theFlashParams.buffer)
#define SET_BUFSIZE_OVERRIDE(new_size) theFlashParams.block_size = (new_size)
#define SET_PAGESIZE_OVERRIDE(new_size) theFlashParams.offset_into_block = (new_size)

// parameter passing structure
typedef struct {
  uint32_t base_ptr;
  uint32_t count;
  uint32_t offset_into_block;
  void *buffer;
  uint32_t block_size;
} FlashParamsHolder;

typedef struct {
  uint32_t start;
  uint32_t length;
} FlashEraseData;

extern FlashParamsHolder theFlashParams;
extern char FlashBufferStart;
extern char FlashBufferEnd;
