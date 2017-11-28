interface IFixHandler;				// 协议处理器(PROTOCOLTYPE_FIX)



// FIX协议处理器
// {AB3D7498-9C4F-4077-93DB-DE4AC6A1D686}
static const IID IID_IFixHandler = { 0xab3d7498, 0x9c4f, 0x4077, { 0x93, 0xdb, 0xde, 0x4a, 0xc6, 0xa1, 0xd6, 0x86 } };
interface IFixHandler : public IHandler
{
};
