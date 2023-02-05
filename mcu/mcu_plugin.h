#ifndef MCU_PLUGIN_H
#define MCU_PLUGIN_H
namespace Gagguino
{
    class MCUPlugin
    {
    public:
        MCUPlugin() = default;
        bool Init();
        void Tick();
    };
}
#endif
