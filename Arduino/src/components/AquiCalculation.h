double BPh, BPl, Ih, Il;
double aqiCalculation(double aqi[6][4], double Cp)
{
    for (int i = 0; i < 6; i++)
    {
        if (Cp >= aqi[i][0] && Cp <= aqi[i][1])
        {
            BPh = aqi[i][1];
            BPl = aqi[i][0];
            Ih = aqi[i][3];
            Il = aqi[i][2];
            break;
        }
    }
    double ppm = ((Ih - Il) / (BPh - BPl)) * (Cp - BPl) + (Il);
    return ppm;
}