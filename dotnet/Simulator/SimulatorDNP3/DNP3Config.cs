﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Automatak.DNP3.Interface;

namespace Automatak.Simulator.DNP3
{
    class DNP3Config : IDNP3Config
    {
        IDictionary<string, DatabaseTemplate> templates = new Dictionary<string, DatabaseTemplate>();
          
        IEnumerable<KeyValuePair<string, DatabaseTemplate>> IDNP3Config.Templates
        {
            get 
            {
                return templates.Select(x => x);
            }
        }

        void IDNP3Config.AddTemplate(string alias, DatabaseTemplate template)
        {
            templates[alias] = template;            
        }


        bool IDNP3Config.ContainsTemplateId(string alias)
        {
            return templates.ContainsKey(alias);
        }


        DatabaseTemplate IDNP3Config.GetTemplateMaybeNull(string alias)
        {
            if (templates.ContainsKey(alias))
            {
                return templates[alias];
            }
            else
            {
                return null;
            }
        }
    }
}
