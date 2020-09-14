from datetime import datetime
import pandas_datareader.data as web
import pandas as pd

symbols = ['ABEV3','AZUL4','B3SA3','BBAS3','BBDC3','BBDC4','BBSE3','BEEF3','BPAC11','BRAP4',
            'BRDT3','BRFS3','BRKM5','BRML3','BTOW3','CCRO3','CIEL3','CMIG4','COGN3','CPFE3',
            'CRFB3','CSAN3','CSNA3','CVCB3','CYRE3','ECOR3','EGIE3','ELET3','ELET6','EMBR3',
            'ENBR3','ENGI11','EQTL3','FLRY3','GGBR4','GNDI3','GOAU4','GOLL4','HAPV3','HGTX3',
            'HYPE3','IGTA3','IRBR3','ITSA4','ITUB4','JBSS3','KLBN11','LAME4','LREN3','MGLU3',
            'MRFG3','MRVE3','MULT3','NTCO3','PCAR3','PETR3','PETR4','QUAL3','RADL3','RAIL3',
            'RENT3','SANB11','SBSP3','SULA11','SUZB3','TAEE11','TIMP3','TOTS3','UGPA3','USIM5',
            'VALE3','VIVT4','VVAR3','WEGE3','YDUQ3']

def daily():
  for symbol in symbols:
    print(symbol)
    f = web.DataReader(symbol+'.SA', 'yahoo', start=datetime(2010, 1, 1), end=datetime(2020, 8, 31), interval='m')
    f.to_csv('ibovespa/'+ symbol + '.csv', columns=['Adj Close'], index_label='Date')

def monthly():
  for symbol in symbols:
    print(symbol)
    f = pd.read_csv('ibovespa/'+ symbol + '.csv', index_col='Date', parse_dates=True).pct_change()
    g = f.resample("M").apply(lambda x: ((x + 1).cumprod() - 1).last("D")).dropna()
    g.to_csv('ibovespa/'+ symbol + 'M.csv', columns=['Adj Close'], index_label='Date', date_format='%Y-%m')

if __name__ == '__main__':
  #daily()
  monthly()
