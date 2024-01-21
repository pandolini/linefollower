%% Oppsett
fis = mamfis("Name", "LFR");

fis = addInput(fis, [0, 240], "Name", "Avvik");
fis = addInput(fis, [-240, 240], "Name", "DAvvik");

fis = addOutput(fis, [-260, 260], "Name", "StyreRetning");

%% Input medlemsfunksjoner

fis = addMF(fis, "Avvik", "zmf", [40, 50], "Name", "SV");
fis = addMF(fis, "Avvik", "trapmf", [40, 50, 75, 90], "Name", "LV");
fis = addMF(fis, "Avvik", "trapmf", [75, 90, 150, 165], "Name", "INGEN");
fis = addMF(fis, "Avvik", "trapmf", [150, 165, 190, 200], "Name", "LH");
fis = addMF(fis, "Avvik", "smf", [190, 200], "Name", "SH");

plotmf(fis, "input", 1);
%figure();

fis = addMF(fis, "DAvvik", "zmf", [-200, -190], "Name", "SVS");
fis = addMF(fis, "DAvvik", "trapmf", [-200, -190, -90, -75], "Name", "LVS");
fis = addMF(fis, "DAvvik", "trapmf", [-90, -75, 75, 90], "Name", "INGEN");
fis = addMF(fis, "DAvvik", "trapmf", [75, 90, 190, 200], "Name", "LHS");
fis = addMF(fis, "DAvvik", "smf", [190, 200], "Name", "SHS");

plotmf(fis, "input", 2);
%figure();

%% Output medlemsfunksjoner

fis = addMF(fis, "StyreRetning", "zmf", [-200, -150], "Name", "SVS");
fis = addMF(fis, "StyreRetning", "trapmf", [-200, -150, -100, -50], "Name", "LVS");
fis = addMF(fis, "StyreRetning", "trapmf", [-100, -50, 50, 100], "Name", "INGEN");
fis = addMF(fis, "StyreRetning", "trapmf", [50, 100, 150, 200], "Name", "LHS");
fis = addMF(fis, "StyreRetning", "smf", [150, 200], "Name", "SHS");

plotmf(fis, "output", 1);
%figure();

%% Regler

regler = [
    "If Avvik is SV and DAvvik is INGEN then StyreRetning is SVS";
    "If Avvik is LV and DAvvik is INGEN then StyreRetning is LVS";
    "If Avvik is INGEN and DAvvik is INGEN then StyreRetning is INGEN";
    "If Avvik is LH and DAvvik is INGEN then StyreRetning is LHS";
    "If Avvik is SH and DAvvik is INGEN then StyreRetning is SHS";
    
    "If Avvik is SV and DAvvik is LVS then StyreRetning is SVS";
    "If Avvik is LV and DAvvik is LVS then StyreRetning is LVS";
    "If Avvik is INGEN and DAvvik is LVS then StyreRetning is INGEN";
    "If Avvik is LH and DAvvik is LVS then StyreRetning is LHS";
    "If Avvik is SH and DAvvik is LVS then StyreRetning is SHS";
    
    "If Avvik is SV and DAvvik is SVS then StyreRetning is SVS";
    "If Avvik is LV and DAvvik is SVS then StyreRetning is SVS";
    "If Avvik is INGEN and DAvvik is SVS then StyreRetning is LVS";
    "If Avvik is LH and DAvvik is SVS then StyreRetning is LVS";
    "If Avvik is SH and DAvvik is SVS then StyreRetning is LVS";
    
    "If Avvik is SV and DAvvik is LHS then StyreRetning is SVS";
    "If Avvik is LV and DAvvik is LHS then StyreRetning is LVS";
    "If Avvik is INGEN and DAvvik is LHS then StyreRetning is INGEN";
    "If Avvik is LH and DAvvik is LHS then StyreRetning is LHS";
    "If Avvik is SH and DAvvik is LHS then StyreRetning is SHS";
    
    "If Avvik is SV and DAvvik is SHS then StyreRetning is LHS";
    "If Avvik is LV and DAvvik is SHS then StyreRetning is LHS";
    "If Avvik is INGEN and DAvvik is SHS then StyreRetning is LHS";
    "If Avvik is LH and DAvvik is SHS then StyreRetning is SHS";
    "If Avvik is SH and DAvvik is SHS then StyreRetning is SHS";];

fis = addRule(fis, regler);

gensurf(fis);

Step = 1;
E = 0:Step:240;
CE = -240:Step:240;
N = length(E);
LookUpTableData = zeros(N);
for i=1:length(E)
   for j=1:length(CE)
      LookUpTableData(i,j) = round(evalfis(fis,[E(i) CE(j)]));
   end
end

writematrix(LookUpTableData, 'table.csv');