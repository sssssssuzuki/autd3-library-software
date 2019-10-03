using AUTD3Sharp;
using System;

namespace AUTD3SharpTest.Test
{
    internal class SimpleExample
    {
        public static void Test()
        {
            Console.WriteLine("Start Simple Test");

            float x = 90.0f;
            float y = 70.0f;
            float z = 150.0f;

            using (AUTD autd = new AUTD())
            {
                autd.Open();
                autd.AddDevice(Vector3f.Zero, Vector3f.Zero);

                Modulation mod = AUTD.SineModulation(150); // AM sin 150 Hz
                autd.AppendModulationSync(mod);

                Gain gain = AUTD.FocalPointGain(x, y, z); // Focal point @ (x, y, z) [mm]
                autd.AppendGainSync(gain);

                Console.WriteLine("press any key to finish...");
                Console.ReadKey(true);
            }
        }
    }
}
