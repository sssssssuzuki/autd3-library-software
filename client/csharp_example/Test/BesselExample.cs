using AUTD3Sharp;
using System;

namespace AUTD3SharpTest.Test
{
    internal class BesselExample
    {
        public static void Test()
        {
            Console.WriteLine("Start BesselBeam Test");

            float x = 83.0f;
            float y = 66.0f;

            using (AUTD autd = new AUTD())
            {
                autd.Open();
                autd.AddDevice(Vector3f.Zero, Vector3f.Zero);

                autd.AppendModulationSync(AUTD.SineModulation(150)); // AM sin 150 HZ

                Vector3f start = new Vector3f(x, y, 0);
                Vector3f dir = Vector3f.UnitZ;
                autd.AppendGainSync(AUTD.BesselBeamGain(start, dir, 13.0f / 180 * AUTD.Pi)); // BesselBeam from (x, y, 0), theta = 13 deg

                Console.WriteLine("press any key to finish...");
                Console.ReadKey(true);
            }
        }
    }
}
