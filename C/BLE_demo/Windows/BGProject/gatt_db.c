#include <stdint.h>
#include "bg_gattdb_def.h"
const uint16_t bg_gattdb_uuidtable_16_map []=
{
    0x2800,
    0x2801,
    0x2803,
    0x1800,
    0x2a00,
    0x2a01,
    0x180a,
    0x2a29,
    0x2902,
};

const uint8_t bg_gattdb_uuidtable_128_map []=
{
0x3a, 0x88, 0x29, 0xd5, 0xdf, 0x67, 0xa7, 0xbb, 0xa9, 0x49, 0xfa, 0x68, 0x46, 0x8d, 0x10, 0x64, 
0x92, 0x24, 0xe8, 0x87, 0xb8, 0x0a, 0xfd, 0xa3, 0x17, 0x4b, 0x48, 0x30, 0x2b, 0x15, 0x1d, 0x45, 
0x08, 0xb0, 0x8d, 0xcb, 0x16, 0x39, 0xdd, 0x92, 0x8a, 0x43, 0xf9, 0xe3, 0xc1, 0x13, 0x55, 0x86, 
};




const struct bg_gattdb_attribute_chrvalue	bg_gattdb_attribute_field_12 = {
	.properties=0x22,
	.index=2,
	.max_len=0,
	.data=NULL,
};

const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_11 = {
	.len=19,
	.data={0x22,0x0d,0x00,0x08,0xb0,0x8d,0xcb,0x16,0x39,0xdd,0x92,0x8a,0x43,0xf9,0xe3,0xc1,0x13,0x55,0x86,}
};
const struct bg_gattdb_attribute_chrvalue	bg_gattdb_attribute_field_10 = {
	.properties=0x08,
	.index=1,
	.max_len=0,
	.data=NULL,
};

const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_9 = {
	.len=19,
	.data={0x08,0x0b,0x00,0x92,0x24,0xe8,0x87,0xb8,0x0a,0xfd,0xa3,0x17,0x4b,0x48,0x30,0x2b,0x15,0x1d,0x45,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_8 = {
	.len=16,
	.data={0x3a,0x88,0x29,0xd5,0xdf,0x67,0xa7,0xbb,0xa9,0x49,0xfa,0x68,0x46,0x8d,0x10,0x64,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_7 = {
	.len=12,
	.data={0x53,0x69,0x6c,0x69,0x63,0x6f,0x6e,0x20,0x4c,0x61,0x62,0x73,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_6 = {
	.len=5,
	.data={0x02,0x08,0x00,0x29,0x2a,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_5 = {
	.len=2,
	.data={0x0a,0x18,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_4 = {
	.len=2,
	.data={0x00,0x00,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_3 = {
	.len=5,
	.data={0x02,0x05,0x00,0x01,0x2a,}
};
uint8_t bg_gattdb_attribute_field_2_data[21];
const struct bg_gattdb_attribute_chrvalue	bg_gattdb_attribute_field_2 = {
	.properties=0x02,
	.index=0,
	.max_len=20,
	.data_varlen=(struct bg_gattdb_buffer_with_len*)bg_gattdb_attribute_field_2_data,
};

const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_1 = {
	.len=5,
	.data={0x02,0x03,0x00,0x00,0x2a,}
};
const struct bg_gattdb_buffer_with_len	bg_gattdb_attribute_field_0 = {
	.len=2,
	.data={0x00,0x18,}
};
const struct bg_gattdb_attribute bg_gattdb_attributes_map[]={
    {.uuid=0x0000,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_0},
    {.uuid=0x0002,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_1},
    {.uuid=0x0004,.permissions=0x01,.datatype=0x02,.dynamicdata=&bg_gattdb_attribute_field_2},
    {.uuid=0x0002,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_3},
    {.uuid=0x0005,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_4},
    {.uuid=0x0000,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_5},
    {.uuid=0x0002,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_6},
    {.uuid=0x0007,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_7},
    {.uuid=0x0000,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_8},
    {.uuid=0x0002,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_9},
    {.uuid=0x8001,.permissions=0x02,.datatype=0x07,.dynamicdata=&bg_gattdb_attribute_field_10},
    {.uuid=0x0002,.permissions=0x01,.datatype=0x00,.constdata=&bg_gattdb_attribute_field_11},
    {.uuid=0x8002,.permissions=0x01,.datatype=0x07,.dynamicdata=&bg_gattdb_attribute_field_12},
    {.uuid=0x0008,.permissions=0x07,.datatype=0x03,.configdata={.flags=0x02,.index=0x02}},
};

const uint16_t bg_gattdb_attributes_dynamic_mapping_map[]={
	0x0003,
	0x000b,
	0x000d,
};

const uint8_t bg_gattdb_adv_uuid16_map[]={0x0};
const uint8_t bg_gattdb_adv_uuid128_map[]={0x08, 0xb0, 0x8d, 0xcb, 0x16, 0x39, 0xdd, 0x92, 0x8a, 0x43, 0xf9, 0xe3, 0xc1, 0x13, 0x55, 0x86, };
const struct bg_gattdb_def bg_gattdb_data={
    .attributes=bg_gattdb_attributes_map,
    .attributes_max=14,
    .uuidtable_16_size=9,
    .uuidtable_16=bg_gattdb_uuidtable_16_map,
    .uuidtable_128_size=3,
    .uuidtable_128=bg_gattdb_uuidtable_128_map,
    .attributes_dynamic_max=3,
    .attributes_dynamic_mapping=bg_gattdb_attributes_dynamic_mapping_map,
    .adv_uuid16=bg_gattdb_adv_uuid16_map,
    .adv_uuid16_num=0,
    .adv_uuid128=bg_gattdb_adv_uuid128_map,
    .adv_uuid128_num=1,
};

const struct bg_gattdb_def *bg_gattdb=&bg_gattdb_data;
