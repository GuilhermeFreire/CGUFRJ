#include "PlanoY.h"

Intersection PlanoY::Intercepta(const Raio& r_vis, IntersectionMode mode, float threshold)
{
  float x,z;

  float t = (a - r_vis.Y0()) / r_vis.Dy();

  Intersection lastIntersection;
  if ( t <0)
    return lastIntersection;

  x = r_vis.X0() +  t * r_vis.Dx();
  if (INSIDE(x,bmin,bmax))
  {
    z = r_vis.Z0() + t *r_vis.Dz();
    if (INSIDE(z,cmin,cmax))
    {
        lastIntersection.setValues(this, t);
        return lastIntersection;
    }
  }
  return lastIntersection;
}

Vetor_3D PlanoY::normal( const Ponto_3D& ponto ) const
{
    return Vetor_3D(0,1,0);
}

TexturePoint PlanoY::pontoTextura(const Ponto_3D& ponto) const
{
    float u = 0, v = 0;
    u =  (ponto.X() - bmin)/(bmax - bmin);
    v =  (ponto.Z() - cmin)/(cmax - cmin);
    return TexturePoint( u,v );
}
