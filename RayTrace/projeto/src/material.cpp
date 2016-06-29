#include <stdio.h>
#include "material.h"

Material::Material(const Cor_rgb& _ambiente,const Cor_rgb& _cor_difusa,
                   const Cor_rgb& _indice_especular, int _n_especular, float _coeficiente_reflexao,
                   float _indice_refracao, float _indice_opacidade , const QImage& tx, bool tt) :
ambiente(_ambiente), cor_difusa(_cor_difusa), indice_especular(_indice_especular), n_especular(_n_especular),
coeficiente_reflexao(_coeficiente_reflexao), indice_refracao(_indice_refracao), indice_opacidade(_indice_opacidade),
textura(tx), temTextura(tt) { }

const Cor_rgb& Material::Ambiente() const
{
    return ambiente;
}

bool Material::hasTexture()const
{
    return temTextura;
}

const Cor_rgb& Material::Cor_difusa()const
{
    return cor_difusa;
}

const Cor_rgb& Material::Indice_especular()const
{
    return indice_especular;
}

Cor_rgb Material::getCorFromTexture(TexturePoint tp)const
{
        int x = tp.U()* textura.width();
        float xp = tp.U()* textura.width() - x;
        float xm = 1 - xp;

        int y = tp.V()* textura.height();
        float yp = tp.V()* textura.height() - y;
        float ym = 1 - yp;

        Cor_rgb pixel1 = textura.pixel(x, y);
        Cor_rgb pixel2 = textura.pixel(x+1, y);
        Cor_rgb pixel3 = textura.pixel(x, y+1);
        Cor_rgb pixel4 = textura.pixel(x+1, y+1);

        pixel1.Multiplica(xm);
        pixel2.Multiplica(xp);
        pixel1.Soma(pixel2);
        pixel3.Multiplica(xm);
        pixel4.Multiplica(xp);
        pixel3.Soma(pixel4);
        pixel1.Multiplica(ym);
        pixel3.Multiplica(yp);
        pixel1.Soma(pixel3);
        return pixel1;
}
