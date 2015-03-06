#ifndef SWE_EXPLICITAPP_H
#define SWE_EXPLICITAPP_H

#include "MooseApp.h"

class SweExplicitApp;

template<>
InputParameters validParams<SweExplicitApp>();

class SweExplicitApp : public MooseApp
{
public:
  SweExplicitApp(const std::string & name, InputParameters parameters);
  virtual ~SweExplicitApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SWE_EXPLICITAPP_H */
