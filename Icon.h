#pragma once

#include <string>

class Icon
{
	private:
		std::string m_name, m_description, m_templatePath;

	public:
		Icon(const std::string& name, const std::string& description, const std::string& templatePath) : m_name(name), m_description(description), m_templatePath(templatePath) {}

		const std::string& getName() const {return m_name;}
		const std::string&  getDescription() const {return m_description;}
		const std::string& getTemplatePath() const {return m_templatePath;}
};