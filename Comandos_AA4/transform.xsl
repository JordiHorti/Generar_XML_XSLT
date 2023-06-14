<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html"/>
  <xsl:template match="/">
    <html>
      <head>
        <style>
          table {
            border-collapse: collapse;
            width: 100%;
          }
          th, td {
            padding: 8px;
            text-align: left;
            border-bottom: 1px solid #ddd;
          }
          .resaltada {
  			border: 2px solid black;
		}
		
        </style>
      </head>
      <body>
        <h1>Datos del adaptador de Red seleccionado</h1>
        <table border="2">
          <tr class="resaltada">
            <th>IP</th>
            <th>Máscara</th>
            <th>Puerta de Enlace</th>
            <th>DNS Primario</th>
            <th>Media</th>
            <th>Número de Saltos</th>
            <th>IP's Saltos</th>           
          </tr>
          <xsl:apply-templates select="datos" />
        </table>
      </body>
    </html>
  </xsl:template>
  
  <xsl:template match="datos">
    <xsl:apply-templates select="IP"/>
    <xsl:apply-templates select="Saltos"/>
  </xsl:template>
  
  <xsl:template match="IP">
    <tr>
      <td><xsl:value-of select="."/></td>
      <td><xsl:value-of select="../Mascara"/></td>
      <td><xsl:value-of select="../PuertaDeEnlace"/></td>
      <td><xsl:value-of select="../DNSPrimario"/></td>
      <td><xsl:value-of select="../Media"/></td>
      <td><xsl:value-of select="../Saltos/NumeroDeSaltos"/></td>
      <td></td>
    </tr>
  </xsl:template>
  
  <xsl:template match="Saltos">
    <tr class="resaltada">
      <td colspan="7" style="background-color: orange;">Saltos</td>
    </tr>
    <xsl:apply-templates select="ip"/>
  </xsl:template>
  
  <xsl:template match="ip">
    <tr> 
      <td><xsl:number value="position()"/></td> 
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td><xsl:value-of select="."/></td>
    </tr>
  </xsl:template>
</xsl:stylesheet>
