
//Your Project
namespace Project;
using System.Runtime.InteropServices;
[ClassInterface(ClassInterfaceType.AutoDual)]
class CSMain
{
    static public bool OnFrame()
    {
        Console.WriteLine("hello c++!");
        return true;
    }
}
