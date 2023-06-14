<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" indent="yes"/>

  <xsl:template match="/datos">
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
        </style>
      </head>
      <body>
        <h2>Información de red</h2>
        <table>
          <tr>
            <th>Datos</th>
            <th>Valor</th>
          </tr>
          <xsl:apply-templates select="IP|Mascara|PuertaDeEnlace|DNSPrimario|Media|Saltos/NumeroDeSaltos"/>
        </table>
        <h3>Saltos</h3>
        <table>
          <tr>
            <th>Índice</th>
            <th>Dirección IP</th>
          </tr>
          <xsl:apply-templates select="Saltos/ip"/>
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="*">
    <tr>
      <td><xsl:value-of select="name()"/></td>
      <td><xsl:value-of select="."/></td>
    </tr>
  </xsl:template>

</xsl:stylesheet>
