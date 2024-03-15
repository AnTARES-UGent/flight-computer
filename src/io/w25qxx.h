/*
    FLASH CHIP W25QXX CLASS 
    Datasheet
    https://www.winbond.com/hq/product/code-storage-flash-memory/serial-nor-flash/?__locale=en&partNo=W25Q16JV
*/

class W25QXX {
    public:
        W25QXX();
        void init();
        void read();
        int test();
        void write();
        void erase();
};