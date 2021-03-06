﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Automatak.DNP3.Interface;

namespace Automatak.Simulator.DNP3.Components
{
    partial class TemplateDialog : Form
    {                
        public TemplateDialog(string alias, DatabaseTemplate template)
        {
            InitializeComponent();

            this.textBoxAlias.Text = alias;

            Configure(template);
        }

        private void buttonADD_Click(object sender, EventArgs e)
        {            
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        public String SelectedAlias
        {
            get
            {
                return textBoxAlias.Text;
            }
        }

        public DatabaseTemplate ConfiguredTemplate
        {
            get
            {
                var template = new DatabaseTemplate(0);
                /* TODO
                template.binaries = templateControlBinary.GetRecords().ToList();
                template.doubleBinaries = templateControlDoubleBinary.GetRecords().ToList();
                template.counters = templateControlCounter.GetRecords().Select(x => new DeadbandRecord<uint>(x.pointClass)).ToList();
                template.frozenCounters = templateControlFrozenCounter.GetRecords().Select(x => new DeadbandRecord<uint>(x.pointClass)).ToList();
                template.analogs = templateControlAnalog.GetRecords().Select(x => new DeadbandRecord<double>(x.pointClass)).ToList();
                template.binaryOutputStatii = templateControlBOStatus.GetRecords().ToList();
                template.analogOutputStatii = templateControlAOStatus.GetRecords().Select(x => new DeadbandRecord<double>(x.pointClass)).ToList();
                 */
                return template;
            }
        }

        private void Configure(DatabaseTemplate template)
        {
            this.templateControlAnalog.SetRecords(template.analogs);
            this.templateControlAOStatus.SetRecords(template.analogOutputStatii);            
            this.templateControlBinary.SetRecords(template.binaries);
            this.templateControlBOStatus.SetRecords(template.binaryOutputStatii);
            this.templateControlCounter.SetRecords(template.counters);
            this.templateControlDoubleBinary.SetRecords(template.doubleBinaries);
            this.templateControlFrozenCounter.SetRecords(template.frozenCounters);            
        }
      
    }
}
