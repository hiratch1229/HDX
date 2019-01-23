#include "IModel.hpp"

#include "CModel.hpp"

IModel* IModel::Create()
{
  return new CModel;
}
