#include "ComponentUser.h"
#include "src/component/ComponentUserBase.h"

void ComponentUser::RemoveComponent(std::string name)
{
    if (HasComponent(name))
        _components.erase(_components.find(name));
    ComponentUserBase::Instance()->DeRegister(name, *this);
}

void ComponentUser::EnableComponent(std::string name)
{
    if(HasComponent(name))
        ComponentUserBase::Instance()->Register(name,*this);
}

void ComponentUser::DisableComponent(std::string name)
{
    if(HasComponent(name))
        ComponentUserBase::Instance()->DeRegister(name,*this);
}

bool ComponentUser::HasComponent(std::string name) const
{
    return _components.find(name) != _components.end();
}

void ComponentUser::AddComponent(Component *component)
{
    std::string component_name = component->GetName();
    _components.insert(std::make_pair(component_name, component));

    ComponentUserBase::Instance()->Register(component_name, *this);
}

std::string ComponentUser::GetComponentValueString(std::string component_name, std::string value_name) const
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return "";
    }
    return _components.at(component_name)->GetStringValue(value_name);
}

void ComponentUser::SetComponentValueString(std::string component_name, std::string component_name_value, std::string value)
{
    _components.at(component_name)->SetStringValue(component_name_value, value);
}

float ComponentUser::GetComponentValueFloat(std::string component_name, std::string value_name) const
{
    if (!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return -1;
    }
    return _components.at(component_name)->GetFloatValue(value_name);
}

void ComponentUser::SetComponentValueFloat(std::string component_name, std::string component_name_value, float value)
{
    _components.at(component_name)->SetFloatValue(component_name_value, value);
}

bool ComponentUser::GetComponentBoolValue(std::string component_name, std::string component_name_value)
{
    if(!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
        return false;
    }
    return _components.at(component_name)->GetBoolValue(component_name_value);
}

void ComponentUser::SetComponentBoolValue(std::string component_name, std::string component_name_value, bool value)
{
    if(!HasComponent(component_name))
    {
        std::cout << "has no component: " << component_name << std::endl;
    }
    _components.at(component_name)->SetBoolValue(component_name_value,value);    
}   


void ComponentUser::CallFunction(std::string component_name, std::string function_name)
{
    _components.at(component_name)->GetFunctionValue(function_name);
}

Component *ComponentUser::GetComponent(std::string name)
{
    return _components.at(name);
}
