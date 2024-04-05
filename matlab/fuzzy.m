%% Oppsett
fis = mamfis("Name", "LFR");

fis = addInput(fis, [0, 140], "Name", "LinjePos");
fis = addInput(fis, [0, 140], "Name", "DLinjePos");

fis = addOutput(fis, [0, 100], "Name", "Kp");
fis = addOutput(fis, [0, 100], "Name", "Kd");

%% Input medlemsfunksjoner

fis = addMF(fis, "LinjePos", "zmf", [20, 35], "Name", "SV");
fis = addMF(fis, "LinjePos", "trapmf", [20, 35, 50, 60], "Name", "LV");
fis = addMF(fis, "LinjePos", "trapmf", [50, 60, 80, 90], "Name", "MIDTEN");
fis = addMF(fis, "LinjePos", "trapmf", [80, 90, 105, 120], "Name", "LH");
fis = addMF(fis, "LinjePos", "smf", [105, 120], "Name", "SH");

plotmf(fis, "input", 1);
figure();

fis = addMF(fis, "DLinjePos", "zmf", [20, 35], "Name", "INGEN");
fis = addMF(fis, "DLinjePos", "trapmf", [20, 35, 50, 60], "Name", "XLS");
fis = addMF(fis, "DLinjePos", "trapmf", [50, 60, 80, 90], "Name", "LS");
fis = addMF(fis, "DLinjePos", "trapmf", [80, 90, 105, 120], "Name", "SS");
fis = addMF(fis, "DLinjePos", "smf", [105, 120], "Name", "XSS");

plotmf(fis, "input", 2);
figure();

%% Output medlemsfunksjoner

fis = addMF(fis, "Kp", "zmf", [0, 20], "Name", "XL");
fis = addMF(fis, "Kp", "trapmf", [0, 20, 30, 40], "Name", "L");
fis = addMF(fis, "Kp", "trapmf", [30, 40, 60, 70], "Name", "M");
fis = addMF(fis, "Kp", "trapmf", [60, 70, 80, 100], "Name", "S");
fis = addMF(fis, "Kp", "smf", [80, 100], "Name", "XS");

plotmf(fis, "output", 1);
figure();

fis = addMF(fis, "Kd", "zmf", [0, 20], "Name", "XL");
fis = addMF(fis, "Kd", "trapmf", [0, 20, 30, 40], "Name", "L");
fis = addMF(fis, "Kd", "trapmf", [30, 40, 60, 70], "Name", "M");
fis = addMF(fis, "Kd", "trapmf", [60, 70, 80, 100], "Name", "S");
fis = addMF(fis, "Kd", "smf", [80, 100], "Name", "XS");

plotmf(fis, "output", 2);
figure();

%% Regler

regler = [
    "If LinjePos is SV and DLinjePos is INGEN then Kp is L, Kd is L";
    "If LinjePos is LV and DLinjePos is INGEN then Kp is XL, Kd is XL";
    "If LinjePos is MIDTEN and DLinjePos is INGEN then Kp is XL, Kd is XL";
    "If LinjePos is LH and DLinjePos is INGEN then Kp is XL, Kd is XL";
    "If LinjePos is SH and DLinjePos is INGEN then Kp is L, Kd is L";
    
    "If LinjePos is SV and DLinjePos is XLS then Kp is L, Kd is L";
    "If LinjePos is LV and DLinjePos is XLS then Kp is L, Kd is L";
    "If LinjePos is MIDTEN and DLinjePos is XLS then Kp is L, Kd is L";
    "If LinjePos is LH and DLinjePos is XLS then Kp is L, Kd is L";
    "If LinjePos is SH and DLinjePos is XLS then Kp is L, Kd is L";
    
    "If LinjePos is SV and DLinjePos is LS then Kp is M, Kd is M";
    "If LinjePos is LV and DLinjePos is LS then Kp is L, Kd is L";
    "If LinjePos is MIDTEN and DLinjePos is LS then Kp is L, Kd is L";
    "If LinjePos is LH and DLinjePos is LS then Kp is L, Kd is L";
    "If LinjePos is SH and DLinjePos is LS then Kp is M, Kd is M";
    
    "If LinjePos is SV and DLinjePos is SS then Kp is S, Kd is S";
    "If LinjePos is LV and DLinjePos is SS then Kp is M, Kd is M";
    "If LinjePos is MIDTEN and DLinjePos is SS then Kp is L, Kd is L";
    "If LinjePos is LH and DLinjePos is SS then Kp is M, Kd is M";
    "If LinjePos is SH and DLinjePos is SS then Kp is S, Kd is S";
    
    "If LinjePos is SV and DLinjePos is XSS then Kp is XS, Kd is XS";
    "If LinjePos is LV and DLinjePos is XSS then Kp is S, Kd is S";
    "If LinjePos is MIDTEN and DLinjePos is XSS then Kp is M, Kd is M";
    "If LinjePos is LH and DLinjePos is XSS then Kp is S, Kd is S";
    "If LinjePos is SH and DLinjePos is XSS then Kp is XS, Kd is XS";];

fis = addRule(fis, regler);

opt1 = gensurfOptions('OutputIndex', 1);
opt2 = gensurfOptions('OutputIndex', 2);
gensurf(fis, opt1);
figure();
gensurf(fis, opt2);
%% 

Step = 1;
E = 0:Step:140;
CE = 0:Step:140;
N = length(E);
LookUpTableDataKp = zeros(N);
LookUpTableDataKd = zeros(N);
for i=1:length(E)
   for j=1:length(CE)
      output = round(evalfis(fis,[E(i) CE(j)]), 0);
      LookUpTableDataKp(i,j) = output(1);
      LookUpTableDataKd(i,j) = output(2);
   end
end

writematrix(LookUpTableDataKp, 'tableKp.csv');
writematrix(LookUpTableDataKd, 'tableKd.csv');