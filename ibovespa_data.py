import pandas as pd
from b3parser import B3Parser
from datetime import datetime

papeis = ['ABEV3','AZUL4','B3SA3','BBAS3','BBDC3','BBDC4','BBSE3','BEEF3','BPAC11','BRAP4',
            'BRDT3','BRFS3','BRKM5','BRML3','BTOW3','CCRO3','CIEL3','CMIG4','COGN3','CPFE3',
            'CRFB3','CSAN3','CSNA3','CVCB3','CYRE3','ECOR3','EGIE3','ELET3','ELET6','EMBR3',
            'ENBR3','ENGI11','EQTL3','FLRY3','GGBR4','GNDI3','GOAU4','GOLL4','HAPV3','HGTX3',
            'HYPE3','IGTA3','IRBR3','ITSA4','ITUB4','JBSS3','KLBN11','LAME4','LREN3','MGLU3',
            'MRFG3','MRVE3','MULT3','NTCO3','PCAR3','PETR3','PETR4','QUAL3','RADL3','RAIL3',
            'RENT3','SANB11','SBSP3','SULA11','SUZB3','TAEE11','TIMP3', 'TIMS3', 'TOTS3','UGPA3','USIM5',
            'VALE3','VIVT4','VVAR3','WEGE3','YDUQ3']

def exportar_cotacao_anual(ano):    
    parser = B3Parser( 'data/COTAHIST_A{0}.TXT'.format( ano ) )
    parser.ler_arquivo( cols_sel = ['data_pregao', 'cod_papel', 'preco_ultimo'], filtros = {})
    parser.exportar_csv( 'data/{0}.csv'.format( ano ) )

def importar_cotacao_anual(ano):
    dateparse = lambda valor: datetime.strptime( valor, '%Y-%m-%d %H:%M:%S' ).date()
    return pd.read_csv('data/{0}.csv'.format( ano ), sep=';', index_col=['data_pregao'], parse_dates=['data_pregao'], date_parser=dateparse)

def calcular_rendimento_mensal():
    cotacao_2020 = importar_cotacao_anual(2020)
    cotacao_2021 = importar_cotacao_anual(2021)
    f = pd.concat([cotacao_2020, cotacao_2021])

    for papel in papeis:
        print(papel)
        df = f.loc[f['cod_papel'] == papel]
        if not df.empty:
            df.to_csv('data/{0}.csv'.format( papel ), columns=['preco_ultimo'], index_label=['data_pregao'], date_format='%Y-%m-%d')
            g = pd.read_csv('data/{0}.csv'.format( papel ), index_col=['data_pregao'], parse_dates=['data_pregao'])
            dg = g.pct_change().resample("M").apply(lambda x: ((x + 1).cumprod() - 1).last("D")).dropna()
            dg.to_csv('data/{0}M.csv'.format( papel ), columns=['preco_ultimo'], index_label=['data_pregao'], date_format='%Y-%m')

if __name__ == '__main__':
    exportar_cotacao_anual(2020)
    exportar_cotacao_anual(2021)
    calcular_rendimento_mensal()
