import pandas as pd
import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
from statsmodels.stats.multicomp import pairwise_tukeyhsd
from statsmodels.stats.multicomp import MultiComparison

def anova_one_to_one( data1, data2 ):
    groups_data1 = data1.groupby( [ "instance" ] )
    groups_data2 = data2.groupby( [ "instance" ] )
    
    instances_data1 = pd.DataFrame( data1["instance"].unique() )
    instances_data1.columns = [ "instance" ]
    instances_data2 = pd.DataFrame( data2["instance"].unique() )
    instances_data2.columns = [ "instance" ]
    
    instances = pd.merge( instances_data1, instances_data2, how="inner",on="instance")
    
    for i in instances[ "instance" ]:
        fvalue, pvalue = stats.f_oneway(
            groups_data1.get_group( i )[ "result" ],
            groups_data2.get_group( i )[ "result" ]
        )
        print( i + "-> " + str( round( pvalue, 4 ) ) )

        if pvalue < 0.05:
            together = pd.concat( [ groups_data1.get_group( i ), groups_data2.get_group( i ) ] )
            mc = MultiComparison( together["result"], together["version"] )
            mc_resuls = mc.tukeyhsd()
            print( mc_resuls )

def anova( data1, data2 ):
    together = pd.concat( [data1, data2 ] )
    
    fvalue, pvalue = stats.f_oneway( data1["result"], data2["result"] )
    print( "fvalue: " + str( fvalue ) )
    print( "pvalue: " + str( pvalue ) )

    if pvalue < 0.05:
        mc = MultiComparison( together["result"], together["version"] )
        mc_resuls = mc.tukeyhsd()
        print( mc_resuls )

def boxplot( data1, data2 ):
    data = pd.DataFrame()
    data["v1"] = data1["result"]
    data["v2"] = data2["result"]

    plot = data.boxplot( column=[ "v1", "v2" ], grid=False )

    fig = plot.get_figure()
    fig.savefig( "v1_vs_v2.png" )

file_v_01 = "../version_01/dataframe.csv"
file_v_02 = "../version_02/dataframe.csv"

data_v_01 = pd.read_csv( file_v_01 )
data_v_02 = pd.read_csv( file_v_02 )

print( "Realizando o teste ANOVA para todos os dados")
anova( data_v_01, data_v_02 )
print("\n\n\n\n")

print( "Realizando o teste ANOVA instância por instância")
anova_one_to_one( data_v_01, data_v_02 )
print("\n\n\n\n")

print("Gerando gráfico")
boxplot( data_v_01, data_v_02 )