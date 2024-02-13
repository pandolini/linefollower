%% Oppsett
fis = mamfis("Name", "LFR");

fis = addInput(fis, [0, 160], "Name", "LinjePos");
fis = addInput(fis, [-140, 140], "Name", "DLinjePos");

fis = addOutput(fis, [-150, 150], "Name", "StyreRetning");

%% Input medlemsfunksjoner

fis = addMF(fis, "LinjePos", "zmf", [20, 35], "Name", "SV");
fis = addMF(fis, "LinjePos", "trapmf", [20, 35, 50, 70], "Name", "LV");
fis = addMF(fis, "LinjePos", "trapmf", [50, 70, 90, 110], "Name", "INGEN");
fis = addMF(fis, "LinjePos", "trapmf", [90, 110, 125, 140], "Name", "LH");
fis = addMF(fis, "LinjePos", "smf", [125, 140], "Name", "SH");

plotmf(fis, "input", 1);
figure();

fis = addMF(fis, "DLinjePos", "zmf", [-120, -85], "Name", "SVS");
fis = addMF(fis, "DLinjePos", "trapmf", [-120, -85, -50, -25], "Name", "LVS");
fis = addMF(fis, "DLinjePos", "trapmf", [-50, -25, 25, 50], "Name", "INGEN");
fis = addMF(fis, "DLinjePos", "trapmf", [25, 50, 85, 120], "Name", "LHS");
fis = addMF(fis, "DLinjePos", "smf", [85, 120], "Name", "SHS");

plotmf(fis, "input", 2);
%figure();

%% Output medlemsfunksjoner

fis = addMF(fis, "StyreRetning", "zmf", [-100, -80], "Name", "SVS");
fis = addMF(fis, "StyreRetning", "trapmf", [-100, -80, -40, -20], "Name", "LVS");
fis = addMF(fis, "StyreRetning", "trapmf", [-40, -20, 20, 40], "Name", "INGEN");
fis = addMF(fis, "StyreRetning", "trapmf", [20, 40, 80, 100], "Name", "LHS");
fis = addMF(fis, "StyreRetning", "smf", [80, 100], "Name", "SHS");

plotmf(fis, "output", 1);
%figure();

%% Regler

regler = [
    "If LinjePos is SV and DLinjePos is INGEN then StyreRetning is SVS";
    "If LinjePos is LV and DLinjePos is INGEN then StyreRetning is LVS";
    "If LinjePos is INGEN and DLinjePos is INGEN then StyreRetning is INGEN";
    "If LinjePos is LH and DLinjePos is INGEN then StyreRetning is LHS";
    "If LinjePos is SH and DLinjePos is INGEN then StyreRetning is SHS";
    
    "If LinjePos is SV and DLinjePos is LVS then StyreRetning is SVS";
    "If LinjePos is LV and DLinjePos is LVS then StyreRetning is LVS";
    "If LinjePos is INGEN and DLinjePos is LVS then StyreRetning is INGEN";
    "If LinjePos is LH and DLinjePos is LVS then StyreRetning is LHS";
    "If LinjePos is SH and DLinjePos is LVS then StyreRetning is SHS";
    
    "If LinjePos is SV and DLinjePos is SVS then StyreRetning is SVS";
    "If LinjePos is LV and DLinjePos is SVS then StyreRetning is SVS";
    "If LinjePos is INGEN and DLinjePos is SVS then StyreRetning is LVS";
    "If LinjePos is LH and DLinjePos is SVS then StyreRetning is LVS";
    "If LinjePos is SH and DLinjePos is SVS then StyreRetning is LVS";
    
    "If LinjePos is SV and DLinjePos is LHS then StyreRetning is SVS";
    "If LinjePos is LV and DLinjePos is LHS then StyreRetning is LVS";
    "If LinjePos is INGEN and DLinjePos is LHS then StyreRetning is INGEN";
    "If LinjePos is LH and DLinjePos is LHS then StyreRetning is LHS";
    "If LinjePos is SH and DLinjePos is LHS then StyreRetning is SHS";
    
    "If LinjePos is SV and DLinjePos is SHS then StyreRetning is LHS";
    "If LinjePos is LV and DLinjePos is SHS then StyreRetning is LHS";
    "If LinjePos is INGEN and DLinjePos is SHS then StyreRetning is LHS";
    "If LinjePos is LH and DLinjePos is SHS then StyreRetning is SHS";
    "If LinjePos is SH and DLinjePos is SHS then StyreRetning is SHS";];

fis = addRule(fis, regler);

gensurf(fis);
%% 

Step = 1;
E = 0:Step:160;
CE = -140:Step:140;
N = length(E);
LookUpTableData = zeros(N);
for i=1:length(E)
   for j=1:length(CE)
      LookUpTableData(i,j) = round(evalfis(fis,[E(i) CE(j)]));
   end
end

writematrix(LookUpTableData, 'table.csv');